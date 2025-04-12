# 🔢 Soma Paralela com Threads em C

Este projeto demonstra como utilizar **threads (POSIX Threads)** para calcular a **soma de um grande vetor de inteiros** de forma paralela, otimizando a performance com múltiplas threads.

---

## 📌 Objetivo

Calcular a soma de 1 milhão de inteiros aleatórios utilizando **4 threads**, dividindo o trabalho entre elas e usando **mutex** para garantir consistência nos dados compartilhados.

---

## ⚙️ Como funciona

1. Um vetor de tamanho `1.000.000` é preenchido com valores aleatórios entre `0` e `99`.
2. O vetor é dividido em 4 partes (uma para cada thread).
3. Cada thread calcula a **soma parcial** do seu segmento.
4. As somas parciais são adicionadas a uma variável global protegida por um **mutex**.
5. Ao final, o resultado é comparado com uma soma sequencial para verificação de consistência.

---

## 🧵 Arquitetura do Código

| Bloco | Descrição |
|-------|-----------|
| `main()` | Inicializa o vetor, cria threads, sincroniza e verifica a soma |
| `soma_parcial()` | Função executada por cada thread para somar uma parte do vetor |
| `DadosThread` | Struct que guarda o intervalo de índice de cada thread |
| `pthread_mutex_t` | Protege a variável global `soma_total` contra condições de corrida |

---

## 📦 Requisitos

- Sistema compatível com POSIX (Linux, Unix, macOS)
- Compilador `gcc`

---

## 🚀 Como compilar e executar

```bash
gcc -o soma_paralela soma_paralela.c -pthread
./soma_paralela
