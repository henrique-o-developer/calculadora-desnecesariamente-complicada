# calculadora-desnecesariamente-complicada

é uma calculadora que é desnecesariamente complicada :)

basicamente uma nova ling, porem atualmente esta em desenvolvimento

[download](https://github.com/henrique-o-developer/calculadora-desnecesariamente-complicada/raw/master/cmake-build-debug/bagulhador.exe)

(/cmake-build-debug/bagulhador.exe)

documentação:

+, -, *, /, !: não preciso nem explicar ne???

COS, TAN, EXP: so aceitam parametros pela frente

SQRT, LOG: o parametro de traz é opcional

DEFINE, ->: o parametro de tras é quevilente ao da frente

IF: a condição vai atras e o codigo na frente (a condição é maior que zero ou não)

PER: aceita o parametro passado por (,) como variavel extra

DECLARE: o parametro de tras é o nome da funcao e o da frente é o codigo

RUN: o parametro de tras é o nome da funcao e o da frente são os argumentos

{[()]}: normal da matematica :)

## não coloque nenhum espaço ou acento poque o cin buga
exemplos:

50 DEFINE 2c<br>
10 DEFINE 1cm<br>
10cm DEFINE 1l<br>

1c -> 1 (transforma 1c em 25)<br>
0.1cm -> 1l (transforma 0.1cm em 0.01l)<br>

## enfase nas variaveis NÃO É POSSIVEL usar letras maiusculas

(1c == 25) IF 35-5; - 0

30 PER 50 (15 ~~ 30 / **100** * 50 ~~)<br>
30 PER 50,150 (10 ~~ 30 / **150** * 50 ~~)<br>

funcaolegal DECLARE $:ARGS0+1:$ (para pegar um parametro use ARGS e o numero do parametro)
funcaolegal RUN 123 (argumentosseparados por virgula)

### esqueci de algo? vai descobrir sosinho :)
