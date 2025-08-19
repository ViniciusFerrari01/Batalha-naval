# Batalha Naval – Nível Básico (Vetores e Matrizes)

Este projeto implementa o **tabuleiro do Batalha Naval** em C para o nível novato, focando em **vetores e matrizes**.

## Regras/Especificação implementada
- Tabuleiro fixo **10x10** representado por uma **matriz**.
- Dois **navios** representados por **vetores** (arrays de tamanho 3).
- Um navio é posicionado **horizontalmente** e o outro **verticalmente**.
- **0** representa **água** e **3** representa **parte do navio**.
- O código **valida limites** e garante **que não há sobreposição**.
- As **coordenadas** dos navios são **definidas no código** (sem ler do usuário).
- O programa **exibe** o tabuleiro com `printf`, com separadores para facilitar a visualização.

## Arquivos
- `batalha_naval_basico.c` — código-fonte em C, bem comentado.
- (Opcional) `Makefile` — atalho de compilação (não obrigatório).

## Compilação e execução
No terminal (Linux/macOS/WSL/MinGW):
```bash
gcc -Wall -Wextra -O2 -std=c11 -o batalha_naval_basico batalha_naval_basico.c
./batalha_naval_basico
```

## Onde alterar as coordenadas
No arquivo `batalha_naval_basico.c`, procure por:
```c
/* ------------------- PARÂMETROS DOS NAVIOS ------------------- */
int  h_linha_inicial = 2;
int  h_coluna_inicial = 1;
char h_orientacao = 'H'; /* 'H' = horizontal */

int  v_linha_inicial = 5;
int  v_coluna_inicial = 7;
char v_orientacao = 'V'; /* 'V' = vertical */
```
Troque os valores de `linha` e `coluna` (0..9) se quiser testar outras posições.

## Entrega no GitHub (passo a passo rápido)
1. Crie um repositório público no GitHub (ex.: `batalha-naval-basico`).
2. Dentro da pasta do projeto, execute:
   ```bash
   git init
   git add batalha_naval_basico.c README.md
   git commit -m "Batalha Naval básico (matriz e vetores)"
   git branch -M main
   git remote add origin https://github.com/<seu-usuario>/batalha-naval-basico.git
   git push -u origin main
   ```
3. Envie o **link do repositório** na plataforma SAVA.

---

> Este exercício NÃO implementa tiros/jogadas. O foco é **conceitos de vetores e matrizes**.
