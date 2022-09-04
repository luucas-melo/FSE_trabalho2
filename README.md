# FSE_trabalho2


Trabalho 2 da disciplina de Fundamentos de Sistemas Embarcados (2022/1)

[Enunciado](https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-2-2022-1)

## Dependências do trabalho

---

* [WiringPi](https://github.com/WiringPi/WiringPi)
* gcc
* make

## Como executar

---

Compile o projeto:

```bash
make
```

Execute o projeto:

```bash
make run
```

## Utilização

---
- Ao iniciar o projeto será necessário informar se a temperatura será do potenciometro ou se será via terminal. Caso seja terminal deve ser digitado a temperatura de referencia e o tempo desejado.

- Para usar o sistema será necessário ligar o sistema e iniciar o aquecimento. Dessa forma será possível visualizar as temperatura interna, o tempo, e a temperatura de referência.

- Ao chegar na temperatura desejada do aquecimento, o tempo definido irá cair de 1 em 1 segundo, e ao final irá parar o aquecimento.

- As informações podem ser visualizadas no lcd.
