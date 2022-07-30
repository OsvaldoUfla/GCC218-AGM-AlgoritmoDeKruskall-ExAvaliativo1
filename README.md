# GCC218-AGM-AlgoritmoDeKruskall-ExAvaliativo1
 Resolução do exercício Problema de Hill Valley do run.codes utilizando AGM: Algoritmo de Kruskall

Problema de Hill Valley
Disciplina: GCC218 - Algoritmos em Grafos

O prefeitura da cidade de Hill Valley, na Califórnia, pretende realizar um choque de gestão e investir fortemente em infraestrutura. Como uma das primeiras medidas, seu prefeito ordenou que a Secretaria de Planejamento elencasse alguns pontos (estabelecimentos) principais na cidade. Após esse levantamento, o prefeito articulou, junto a empresas e o poder público, um projeto para ampliação da capacidade da usina de produção energética denominada "Força". Por sinal, o ponto ao qual a usina "Força" está localizada é um dos principais.

Para tanto, um grupo de engenheiros eletricistas da empresa "Fiat Lux", contratados pela prefeitura, informou que o êxito do plano energético de Hill Valley passaria pela seguinte condição: os pontos principais destacados pela Secretaria de Planejamento devem se conectar diretamente à usina "Força" ou a algum outro ponto que possua alcançabilidade a "Força". A "Fiat Lux" entregou à prefeitura um relatório que indicava os custos de conexão entre todos os pontos principais da cidade.

O prefeito sabe do volume de recursos que serão gastos para a execução desse projeto. Assim, solicitou a uma outra empresa contratada, a "Opt+", a indicação de dois projetos de interligação dos pontos com o menor custo possível. Com isso, a prefeitura poderia analisá-los e escolher o mais aderente à cidade. O prefeito deixou claro para a "Opt+" que o custo para a implantação de um projeto seria dado pela soma dos custos das conexões entre os pontos principais.

Você é um empregado recém-contratado da "Opt+", o único do time desse projeto que cursou GCC218. Seu gerente, sabendo disso, o designou prontamente à tarefa de elaborar uma solução eficiente para a prefeitura de Hill Valey.

Auxilie sua equipe a resolver esse desafio, que contribuirá muito para a prosperidade econômica desse município.

Entradas
A primeira linha da entrada consistirá na quantidade de casos de teste a serem resolvidos, denotada por 1 < T < 15. Cada um dos T casos de teste aparecem na sequência. A primeira linha de cada caso de teste é composta por dois inteiros: 3 < N < 100 (quantidade de pontos principais em Hill Valley) e M (quantidade de possíveis ligações entre os N pontos). As próximas M linhas possuem, cada uma delas, três inteiros: A, B, C, indicando que entre os pontos A, B existe uma possibilidade de conexão, com custo igual a 1 < C < 300. Os pontos principais de Hill Valley são identificados por inteiros de 1 a N.

Saídas
Cada caso de teste será impresso em apenas uma linha. Cada linha deve conter dois inteiros, separados por apenas um espaço em branco, que representam os custo de implementação dos dois projetos de infraestrutura energética de menor valor em Hill Valley.

Exemplo de Entrada
2
5 8\
1 3 75
3 4 51
2 4 19
3 2 95
2 5 42
5 4 31
1 2 9
3 5 66
9 14
1 2 4
1 8 8
2 8 11
3 2 8
8 9 7
8 7 1
7 9 6
9 3 2
3 4 7
3 6 4
7 6 2
4 6 14
4 5 9
5 6 10

Exemplo de Saída
110 121
37 37
