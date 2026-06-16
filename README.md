# Donkey Kong Game

## Configurando a raylib

Após clonar o projeto, também é necessário compilar a raylib.

### 1. Clonar o repositório com os submódulos

```bash
git clone --recursive https://github.com/marianairigaray/DK_Game.git
```

Se o projeto já foi clonado:

```bash
git submodule update --init --recursive
```

### 2. Compilar a raylib

```bash
cd libs/raylib/src
make
```

### 3. Voltar para a pasta do projeto

```bash
cd ../../..
```

### 4. Compilar o jogo

```bash
make
```

### 5. Executar o jogo

```bash
make run
```