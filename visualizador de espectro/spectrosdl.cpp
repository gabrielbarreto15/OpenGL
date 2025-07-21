// Visualizador de espectro de MP3 com SDL2, FFTW e OpenGL (ajuste de logscale e
// balanceamento de bandas)

#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <fftw3.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// === PARÂMETROS === //
constexpr int SAMPLE_RATE = 44100;
constexpr int CHANNELS = 2;
constexpr int FFT_SIZE = 512;
constexpr int BANDS = 64;
constexpr float DB_RANGE = 40.0f;
constexpr float SPECTRUM_MULTIPLIER = 1e-2f;

// === BUFFERS === //
double* fftIn;
fftw_complex* fftOut;
fftw_plan fftPlan;
std::vector<float> window(FFT_SIZE);
std::vector<float> logscale(BANDS + 1);
std::vector<float> spectrum(BANDS);
std::vector<float> maxspectrum(BANDS);

// === FUNÇÕES AUXILIARES === //
inline float CLAMP(float val, float minv, float maxv) {
  return std::max(minv, std::min(maxv, val));
}

void initWindowAndScale() {
  for (int i = 0; i < FFT_SIZE; ++i)
    window[i] = 0.5f * (1 - cos(2 * M_PI * i / (FFT_SIZE - 1)));

  // Distribuição logarítmica corrigida
  float minLog = log10f(1.0f);
  float maxLog = log10f(FFT_SIZE / 2.0f);
  for (int i = 0; i <= BANDS; ++i) {
    float logIndex = pow(10.0f, minLog + (maxLog - minLog) * i / BANDS) - 1.0f;
    logscale[i] = CLAMP(logIndex, 0.0f, FFT_SIZE / 2.0f - 1.0f);
  }
}

// === CALLBACK DE ÁUDIO === //
void audioCallback(void* udata, Uint8* stream, int len) {
  spectrum;  // Armazena o espectro anterior

  if (!stream || len < FFT_SIZE * CHANNELS * (int)sizeof(Sint16)) return;

  Sint16* samples = reinterpret_cast<Sint16*>(stream);
  for (int i = 0; i < FFT_SIZE; ++i) {
    float l = samples[2 * i] / 32768.0f;
    float r = samples[2 * i + 1] / 32768.0f;
    float mono = (l + r) * 0.5f;
    fftIn[i] = mono * window[i];
  }

  fftw_execute(fftPlan);

  std::vector<float> magnitudes(FFT_SIZE / 2);
  for (int i = 0; i < FFT_SIZE / 2; ++i) {
    float re = fftOut[i][0];
    float im = fftOut[i][1];
    float amplitude = SPECTRUM_MULTIPLIER * sqrtf(re * re + im * im);
    magnitudes[i] = CLAMP(amplitude, 0.0f, 1.0f);
  }

  for (int i = 0; i < BANDS; ++i) {
    int a = ceilf(logscale[i]);
    int b = floorf(logscale[i + 1]);
    float sum = 0;

    if (b < a) {
      sum += magnitudes[b] * (logscale[i + 1] - logscale[i]);
    } else {
      if (a > 0) sum += magnitudes[a - 1] * (a - logscale[i]);
      for (int j = a; j < b; ++j) sum += magnitudes[j];
      if (b < FFT_SIZE / 2) sum += magnitudes[b] * (logscale[i + 1] - b);
    }

    sum *= FFT_SIZE / 24.0f;
    float dB = 20.0f * log10f(sum + 1e-6f);
    float val = 1.0f + dB / DB_RANGE;
    spectrum[i] = CLAMP(val, 0.0f, 1.0f);
    // spectrum[i] = val; // Removido para garantir que o CLAMP seja o valor final
  }
  // normalize spectrum to [0, 1]
  float minVal = *std::min_element(spectrum.begin(), spectrum.begin() + BANDS);
  // std::cout << "Min: " << minVal << std::endl;
  if (minVal < 0.0f) {
    for (int i = 0; i < BANDS; ++i) {
      spectrum[i] -= minVal;  // Ajusta para que o mínimo seja 0
    }
  }
  float maxVal = *std::max_element(spectrum.begin(), spectrum.begin() + BANDS);
  // std::cout << "Max: " << maxVal << std::endl;
  //  Normaliza o espectro para o intervalo [0, 1]
  //  Isso garante que o espectro esteja sempre entre 0 e 1
  //  mesmo que o valor máximo seja negativo ou zero
  //  Isso é importante para evitar problemas de visualização
  //  quando o espectro é muito baixo ou negativo
  //  e para garantir que o espectro seja sempre visível
  //  e para garantir que o espectro seja sempre visível
  if (maxVal > 0.0f) {
    for (int i = 0; i < BANDS; ++i) {
      spectrum[i] /= maxVal;
    }
  }

  glutPostRedisplay();
}

// === OPENGL === //
void display() {
  static int frameCount = 0;
  frameCount++;

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  glBegin(GL_TRIANGLE_STRIP); // Começa a desenhar uma tira de triângulos
  for (int i = 0; i < BANDS; ++i) {
    float x = static_cast<float>(i);
    float h = maxspectrum[i];

    // Cores gradientes 
    float r = 0.5f + 0.5f * sin(2 * M_PI * i / BANDS + 0.0f);
    float g = 0.5f + 0.5f * sin(2 * M_PI * i / BANDS + M_PI / 3.0f);
    float b = 0.5f + 0.5f * sin(2 * M_PI * i / BANDS + 2 * M_PI / 3.0f);

    // Vértice na base (y=0)
    glColor3f(r * 0.5f, g * 0.5f, b * 0.5f); // Cor mais escura para a base
    glVertex2f(x, 0.0f);

    // Vértice na altura da curva
    glColor3f(r, g, b); // Cor para o pico da curva
    glVertex2f(x, h);
  }
  glEnd();

  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, BANDS, 0.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
}

void idle() {
  // Fator de suavização
  float smoothing_factor = 0.01f;

  // Velocidade mínima de decaimento para garantir que as barras cheguem a zero
  float min_decay_speed = 0.005f;

  for (int i = 0; i < BANDS; ++i) {
    maxspectrum[i] = std::max(spectrum[i], maxspectrum[i]);
    maxspectrum[i] = maxspectrum[i] * (1.0f - smoothing_factor) + spectrum[i] * smoothing_factor;
    if (spectrum[i] < maxspectrum[i]) { // Apenas decaia se o espectro atual for menor
        maxspectrum[i] -= min_decay_speed;
    }
    // Garante que os valores permaneçam dentro dos limites de 0 a 1.
    maxspectrum[i] = CLAMP(maxspectrum[i], 0.0f, 1.0f);
  }

  glutPostRedisplay();
}

void initGL() {
  glClearColor(0, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

// === MAIN === //
int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <arquivo.mp3>" << std::endl;
    return 1;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 400);
  glutCreateWindow("Visualizador de Espectro");
  initGL();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(
      [](unsigned char key, int x, int y) {  // Função de callback de teclado
        if (key == 27) {                     // Tecla ESC
          exit(0);                           // Sai do loop principal do GLUT
        }
      });

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "Erro SDL: " << SDL_GetError() << std::endl;
    return 1;
  }

  if (Mix_OpenAudio(SAMPLE_RATE, MIX_DEFAULT_FORMAT, CHANNELS, 4096) < 0) {
    std::cerr << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  fftIn = (double*)fftw_malloc(sizeof(double) * FFT_SIZE);
  fftOut = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * FFT_SIZE);
  fftPlan = fftw_plan_dft_r2c_1d(FFT_SIZE, fftIn, fftOut, FFTW_ESTIMATE);
  initWindowAndScale();
  Mix_SetPostMix(audioCallback, nullptr);

  Mix_Music* music = Mix_LoadMUS(argv[1]);
  if (!music) {
    std::cerr << "Erro Mix_LoadMUS: " << Mix_GetError() << std::endl;
    return 1;
  }
  Mix_PlayMusic(music, -1);

  glutMainLoop();

  fftw_destroy_plan(fftPlan);
  fftw_free(fftIn);
  fftw_free(fftOut);
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}