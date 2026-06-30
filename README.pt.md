# physics-simulator

Aplicação desktop em GTK4 que simula física de partículas em dois modos — cinemático e dinâmico — desenvolvida para a cadeira de Programação e Algoritmos.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-concluído-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Make](https://img.shields.io/badge/Make-4495D5?logo=make&logoColor=white)](https://www.gnu.org/software/make/)
[![GTK4](https://img.shields.io/badge/GTK-4-4A86CF?logo=gnome&logoColor=white)](https://docs.gtk.org/gtk4/)

Português | [English](README.md)

## Sobre

Simulador de partículas com dois modos independentes. No modo cinemático as partículas seguem trajetórias com aceleração constante; no modo dinâmico a segunda lei de Newton é aplicada com forças e gravidade configuráveis. A interface é construída com GTK4 e Blueprint, e as simulações são renderizadas com Cairo.

## Modos de simulação

| Modo           | Descrição                                                                                      |
| -------------- | ---------------------------------------------------------------------------------------------- |
| **Cinemático** | Aceleração constante — posição e velocidade actualizadas via s = s₀ + v·t + ½·a·t².            |
| **Dinâmico**   | Aceleração variável — força resultante dividida pela massa origina a aceleração em cada passo. |

## Funcionalidades

- **Gráficos vetoriais**: Renderiza partículas, velocidades e forças com as suas magnitudes e direções usando Cairo.
- **Controlos de simulação**: Inicie, pare e reinicie simulações ajustando os passos de tempo, frames por segundo, duração e gravidade.
- **Controlos de câmara**:
  - **Zoom automático**: Escala dinamicamente a área visível para focar todas as partículas.
  - **Seguir partícula**: Foca a câmara numa partícula específica, mantendo-a centralizada.
- **Rastos**: Desenha o percurso histórico das partículas.
- **Exportação de dados**: Guarda automaticamente registos detalhados da simulação em ficheiros CSV, contendo posições, velocidades e forças a cada instante.
- **Projetos**: Guarde e carregue as simulações através de ficheiros de projeto `.sabino`.

## Requisitos

| Ferramenta         | Versão |
| ------------------ | ------ |
| GCC                | 9+     |
| Make               | 4+     |
| GTK4               | 4.0+   |
| Blueprint Compiler | 0.8+   |
| Cairo              | 1.16+  |
| GLib               | 2.0+   |

Testado em Fedora/GNOME. Execução nativa em macOS não é suportada.

## Como executar

```bash
make run          # compilar e lançar o simulador
make all_tests    # executar todos os testes unitários
make clean        # remover artefactos de build
```

## Licença

Distribuído sob a licença **MIT**, © 2024 Nycolas Souza.

O texto completo está em [LICENSE](LICENSE).
