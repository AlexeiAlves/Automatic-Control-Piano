# Automatic-Control-Piano
Integrantes:Alexei Alves de Souza ;
Gustavo Bezerra Fechine ;
André Gadelha.
O que é o Projeto:
  O Self Control Piano é um projeto para o desenvolvimento de um piano digital em miniatura capaz de reproduzir os sons e movimentos de uma sequência de notas musicais com o objetivo de auxiliar no aprendizado de amantes da música.
  
  Ele deverá ser controlado por um microcontrolador que receberá a sequência de notas musicais e reproduzirá seus movimentos e sons através de uma estrutura mecânica baseada em um sistema de selação das respectivas teclas a serem pressionadas.
  
  A princípio o projeto visa abordar apenas partituras simples, como o dedilhamento de notas musicais, porém no decorrer de seu desenvolvimento poderão ser abordados mais detalhes inerentes ao aperfeiçoamento dos sons e configuração de acordes mais complexos.
  
 Tutorial do Projeto :
    Escolher o modo 1 ou 2, Azul -> ok; Vermelho ->Digito Inválido
    Modo 1 : Piano toca sozinho.
      Escolhe quantas teclas devem ser tocados até 2 digitos de teclas.
        Digitadas as notas que serão tocadas o led verde acende para mostrar que o piano irá tocar.
    Modo 2 : Usuário toca no teclado
 
 Limitações :
  Neste projeto não há um modo de o usuário tocar o teclado e fornecer o som pois não foi elaborado um teclado matricial horizontal, o que seria um acréscimo complexo para projetos  de aperfeiçoamento.
  Ele também toca apenas uma nota de cada vez e é capaz de armazenar apenas até 99 notas.
  É limitado pelo tempo de execução do movimento do servo motor.
  Não há controle de discretização do tempo de cada nota, restringindo a possibilidade de executar musicas mais complexas.
  
  Aperfeiçoamento: é necessário implementar o teclado matricial nas teclas físicas do piano eletronico. Imaginando uma nova etapa de desenvolvimento podemos implementar mais atuadores simulando a mão humana, uma função de gravação/execução de musicas na memória e depois disso a imaginação é o limite.

Link para o vídeo de teste do projeto:
https://youtu.be/pmSFyxgd_6Q
