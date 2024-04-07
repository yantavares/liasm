# Linguagem Inventada - liasm (PT-BR)

![Estrelas](https://img.shields.io/github/stars/yantavares/liasm)
[![Licença: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

Para a versão em inglês, clique [aqui](README.md).

Bem-vindo ao repositório da Linguagem Inventada, uma simulação de máquina que permite montar e executar programas escritos na "Linguagem Inventada" ou `liasm`, criada pela Universidade de Brasília (UnB).

## Descrição da Máquina Hipotética

O ambiente `liasm` é projetado para emular uma arquitetura de computador simples. A máquina hipotética em seu núcleo tem os seguintes componentes:

- **ACC**: Um registrador acumulador de 16 bits para operações aritméticas e lógicas.
- **PC**: Um registrador contador de programa de 16 bits que aponta para a próxima instrução.
- **Memória**: Uma memória com \( 2^{16} \) palavras, cada uma com 16 bits.

Esta máquina reconhece três formatos de instrução:

- Formato 1: Opcode único
- Formato 2: Opcode seguido por um endereço
- Formato 3: Opcode seguido por dois endereços

O conjunto de instruções é projetado para ser minimalista, mas completo, permitindo a implementação de uma ampla gama de algoritmos.

---

## Linguagem de Montagem liasm

Embora simples, `liasm` pode ser considerada uma linguagem Turing completa. Ela possui um conjunto de instruções e diretivas que permitem ao programador escrever programas complexos. A tabela a seguir lista as instruções disponíveis:

| Mnemônico | Opcode Numérico | Tamanho (palavras) | Ação                    |
| --------- | --------------- | ------------------ | ----------------------- |
| ADD       | 01              | 2                  | ACC <- ACC + mem(OP)    |
| SUB       | 02              | 2                  | ACC <- ACC - mem(OP)    |
| MUL       | 03              | 2                  | ACC <- ACC \* mem(OP)   |
| DIV       | 04              | 2                  | ACC <- ACC ÷ mem(OP)    |
| JMP       | 05              | 2                  | PC <- OP                |
| JMPN      | 06              | 2                  | Se ACC<0 então PC <- OP |
| JMPP      | 07              | 2                  | Se ACC>0 então PC <- OP |
| JMPZ      | 08              | 2                  | Se ACC=0 então PC <- OP |
| COPY      | 09              | 3                  | mem(OP2) <- mem(OP1)    |
| LOAD      | 10              | 2                  | ACC <- mem(OP)          |
| STORE     | 11              | 2                  | mem(OP) <- ACC          |
| INPUT     | 12              | 2                  | mem(OP) <- entrada      |
| OUTPUT    | 13              | 2                  | saída <- mem(OP)        |
| STOP      | 14              | 1                  | Suspende a execução     |
| THROW     | 15              | 1                  | Lança uma exceção       |
| NOP       | 16              | 1                  | Incrementa PC em 1      |

Diretivas:

- CONST: Aloca um valor constante para um endereço de memória.
  Exemplo: `N3: CONST 1 ; Aloca 1 para N3`
- SPACE: Aloca espaço de memória para um endereço sem inicializá-lo.
  Exemplo: `N1: SPACE ; Aloca memória para o endereço N1`

Comentários:

- Comentários no código de montagem `liasm` começam com um ponto e vírgula (`;`).
  Tudo que segue o `;` em uma linha é considerado um comentário e é ignorado pelo montador.

## Fluxo de Trabalho do Compilador

O compilador `liasm` opera em duas passagens:

1. **Primeira Passagem**: O compilador lê o arquivo fonte `.liasm` para construir uma tabela de rótulos, que é usada para resolver endereços durante o processo de montagem. Durante esta fase, o compilador também realiza análise léxica para identificar quaisquer erros de sintaxe no código fonte.

2. **Segunda Passagem**: Com a tabela de rótulos construída, o compilador lê o arquivo fonte uma segunda vez, desta vez traduzindo as instruções de montagem

para o código binário. O compilador também realiza verificações semânticas para garantir a integridade do programa, como validar formatos de instrução e detectar referências indefinidas.

## Estrutura do Projeto

Aqui está uma visão geral da estrutura do projeto para ajudá-lo a navegar e entender seus componentes:

- **`liasm/`**: O diretório principal contendo todos os recursos necessários para o montador e simulação.
  - **`bin/`**: Armazena os binários compilados do montador.
  - **`examples/`**: Contém exemplos de código de Montagem Inventiva para testes e aprendizado.
  - **`includes/`**: Cabeçalhos de bibliotecas usadas pelo montador.
  - **`src/`**: Código fonte do montador.
  - **`tests/`**: Testes automatizados.
  - **`utils/`**: Ferramentas auxiliares.
  - **`compiler.cpp`**: O arquivo principal do compilador.
  - **`Makefile`**: Para compilar o projeto usando `make`.
  - **`RAM.txt`** e **`ROM.txt`**: Simulam arquivos de memória RAM e ROM, respectivamente.
- **`.gitignore`**: Lista de arquivos/diretórios a ignorar na versionamento.
- **`README.md`**: Documentação (este arquivo).

## Primeiros Passos

### Pré-requisitos

Antes de começar, certifique-se de que as seguintes ferramentas estão instaladas no seu sistema:

- **`make`**: Utilitário para automação de compilação.
- **`g++`**: O compilador C++ da Coleção de Compiladores GNU (GCC).

### Montando e Executando Programas com `licc`

Para compilar o montador `licc`:

1. **Navegue até o diretório do projeto**:

   ```bash
   cd liasm/
   ```

2. **Compile o montador** usando o comando `make`:

   ```bash
   make
   ```

Ou você pode apenas usar o binário pré-compilado no diretório `liasm`.

#### Usando Makefile

Após compilar o montador:

- **Para montar um programa**, substitua `<caminho do arquivo>` pelo seu arquivo `.asm`:

  ```bash
  ./licc <caminho do arquivo>
  ```

- **Opcional**: Você também pode definir o modo para `debug` para ver os rótulos gerados e a saída verbosa.

  ```bash
  ./licc <caminho do arquivo> debug
  ```

#### Execução Direta com `make run`

- **Para compilar o montador e executar diretamente**, substitua `<Caminho do arquivo>` pelo caminho do seu arquivo `.asm`:

  ```bash
  make run FILE=<Caminho do arquivo>
  ```

- **Opcional**: Você também pode definir o modo para `debug` para ver os rótulos gerados e a saída verbosa.

  ```bash
  make run FILE=<Caminho do arquivo> MODE=debug
  ```

### Executando Testes

Para garantir que o montador está funcionando corretamente:

```bash
make test
```

Este comando compila o montador e executa todos os testes na pasta `tests/`.

## Licença

Este projeto está sob a UNLICENSE, permitindo total liberdade para uso, modificação e distribuição.
