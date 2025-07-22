# Visualizador de espectro de áudio com OpenGL

## Descrição

Este projeto implementa um visualizador de espectro de áudio em C++ utilizando as bibliotecas:

1. SDL2
2. SDL2_mixer
3. FFTW3
4. OpenGL

Esse projeto tem o intuito de captar um arquivo
de áudio, aplicar FFT e exibir seu espctro com o OpenGL.

## Instalação

Para instalação das dependência no Windows com vcpkg. Você deve instalar o vcpkg na sua máquina e depois executar o seguinte comando para instalar as dependências:

```bash
vcpkg install sdl2 sdl2-mixer fftw3 freeglut
```

## Compilação

Para a compilação foi utilizado o CMake com vcpkg. Todos os arquivos necessários já estão configurados na pasta do projeto, como: CMakeLists.txt e vcpkg.json.

Assim, para compilar e excutar basta digitar o comando dentro da pasta:

```bash
cmake --build build --config Release
```

E depois que o executável foi gerado na pasta /build/Realease vá até ela e execute o comando:

```bash
.\spectrosdl.exe arquivo.wav
```

Lembrando que seu arquivo de aúdio deve está na mesma pasta do executável.
