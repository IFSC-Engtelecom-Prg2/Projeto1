# Introdução ao uso do github com o CLion

O git é um sistema de controle de versão de arquivos, e que foi projetado para ajudar no projeto de desenvolvimento de software. Com ele se pode acompanhar o histórico de modificações feitos nos arquivos de um projeto, os quais formam um **repositório** git. Ele facilita muito o trabalho em equipe, pois diferentes desenvolvedores podem:
* Clonarem um repositório git remoto, e assim obterem os arquivos do projeto dentro de um repositório local
* Efetuarem suas modificações nesses arquivos, e em seguida registrarem-nas em seus repositório locais (fazerem **commit**)
* Enviarem suas modificações para o repositório git remoto (fazerem **push**), para que fiquem disponíveis para toda a equipe

Nas aulas de PRG2 o git já vem sendo usado quase de forma implícita. Todos os exercícios realizados até o momento envolveram usar o git para obter seus arquivos de projeto CLion. No entanto, o uso do git foi muito básico, pois se limitou a clonar um repositório disponibilizado no github. Para explorar mais o que o git tem a oferecer, é necessário entender o ciclo básico de atualizações de arquivos em um repositório.

**OBS:** antes de continuar, certifique-se de que o programa *git* esteja instalado em seu computadir. Execute este comando em um terminal:

```
sudo apt install git
```

Como já foi visto, o primeiro passo é clonar um repositório remoto existente no github. Em seguida podem-se modificar arquivos do projeto, fazendo-se *commit* quando achar adequado. Ao final, devem-se publicar as modificações no repositório remoto (*push*). O video a seguir mostra esse processo para a tarefa do Projeto 1.
* [Clonando o projeto 1](http://tele.sj.ifsc.edu.br/~msobral/prg2/2020-1/git-clion.mp4): fazendo modificações, e depois enviando-as ao repositório remoto no github.


Uma vez tendo o repositório clonado, nas próximas vzes em que se for trabalhar no projeto deve-se seguir este procedimento:
1. Use a operação **push** para obter as modificações no projeto feitas por outros membros da equipe. Essas modificações devem estar no repositório no github.
1. Trabalhe normalmente nos arquivos do projeto em seu repositório local. Quando concluir suas modificações, faça a operação **commit** para registrá-las em seu repositório.
1. Use a operação **push** para enviar suas modificações para o repositório do github

O video a seguir ilustra essa sequência de trabalho usando o git:
* [Trabalhando em seu repositório](http://tele.sj.ifsc.edu.br/~msobral/prg2/2020-1/git-clion-2.mp4): ao final, o repositório remoto no github deve estar sincronizado com seu repositório local


Tudo muito simples, mas ... e se ocorrerem conflitos entre as modificações feitas por diferentes desenvolvedores ? Bem, isso é assunto para outro momento ! Por enquanto, leia estes tutoriais, pois eles explicam o git com um pouco mais de detalhes:
* [Uma introdução ao uso do github](https://kinsta.com/pt/base-de-conhecimento/que-github/): ignorar as menções ao Wordpress
* [Conceitos básicos sobre git](https://www.extra-imagens.com.br/Control/ArquivoExibir.aspx?IdArquivo=98301252&Attachment=1): precisamos somente saber o necessário para um ciclo de atualizações d um projeto. Para isso, é suficiente saber o que é *commit*, *pull*, *push* e *merge*.
* [Um guia básico sobre git](https://tableless.com.br/tudo-que-voce-queria-saber-sobre-git-e-github-mas-tinha-vergonha-de-perguntar/): apesar de este guia focar no uso do git na linha de comando, ele mostra de forma clara muitos conceitos sobre git



