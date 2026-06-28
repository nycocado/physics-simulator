# physics-simulator

Aplicação desktop em GTK3 que simula física de partículas em dois modos — cinemático e dinâmico — desenvolvida para a cadeira de Programação e Algoritmos.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-concluído-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Make](https://img.shields.io/badge/Make-4495D5?logo=make&logoColor=white)](https://www.gnu.org/software/make/)
[![GTK3](https://img.shields.io/badge/GTK-3-4A86CF?logo=gnome&logoColor=white)](https://docs.gtk.org/gtk3/)

Português | [English](README.md)

## Sobre

Simulador de partículas com dois modos independentes. No modo cinemático as partículas seguem trajetórias com aceleração constante; no modo dinâmico a segunda lei de Newton é aplicada com forças e gravidade configuráveis. A interface é construída com GTK3 e Glade, e as simulações são renderizadas com Cairo.

## Modos de simulação

| Modo | Descrição |
| ---- | --------- |
| **Cinemático** | Aceleração constante — posição e velocidade actualizadas via s = s₀ + v·t + ½·a·t². |
| **Dinâmico** | Aceleração variável — força resultante dividida pela massa origina a aceleração em cada passo. |

## Requisitos

| Ferramenta | Versão |
| ---------- | ------ |
| GCC | 9+ |
| Make | 4+ |
| GTK3 | 3.24+ |
| Cairo | 1.16+ |
| GLib | 2.0+ |

Testado em Ubuntu/GNOME. Execução nativa em macOS não é suportada.

## Como executar

```bash
make run          # compilar e lançar o simulador
make phy_test     # executar testes unitários de física
make clean        # remover artefactos de build
```

## Licença

Distribuído sob a licença **MIT**, © 2024 Nycolas Souza.

O texto completo está em [LICENSE](LICENSE).
