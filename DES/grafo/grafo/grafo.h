/***************************************************************************
*
* $MCD Módulo de definição: GRA GRAFO Genérico 
*
* Arquivo gerado: grafo.h
* Letras identificadoras: GRA
*
* Nome da base de software: Arcabouço para a automação de testes de programas redigidos em C
*
* Projeto: INF 1301 Trabalho 4
* Gestor: LES/DI/PUC-Rio
* Autores:  Lucas Menezes <LM>, Lorenzo Saraiva <LS>
*
* $HA Histórico de evolução:
* Versão Autor Data Observações
* 1     LM,LS 22/set/2014 Início do Desenvolvimento
* 2		LM,LS 23/OUT/2014 início da melhoria do módulo
* 3		LM,LS 01/DEZ/2014 Início da instrumentação
* $ED Descrição do módulo
* Implementa Um grafo genérico não dirigido, i.e. , 
* (para todo nó A e B) A está ligado em B <=> B está ligado em A.
* 
* O grafo é definido como um conjunto de vértices (ou nós) e suas arestas.
* 
* Cada vértice gerado é identificado por um inteiro >= 1 e não há dois vértice com 
* a mesma identificação coexistindo no mesmo grafo.
* 
* As operações com vértices e arestas são feitas indicando as identificações dos vértices envolvidos
* Ao Criar um vértice, a identificação dele é fornecida ao usuário, 
* para que possa ser posteriormente operado
* 
* Podem existir n grafos em operação simultaneamente.
* Os grafos possuem uma cabeça encapsulando o seu estado.
* 
* Alternativamente aos indices dos nós, os grafos podem ser operados por operações
* de elemento corrente
*
* Cada grafo é homogêneo quanto ao tipo dos dados que armazena.
* Cada vértice do grafo referencia o valor que contém.
*
* Os ponteiros para os dados são copiados para elementos da grafo
* Não é copiado o valor apontado por estes ponteiros.
*
* O controle da destruição do valor de um vértice a ser excluído
* é realizado por uma função fornecida pelo usuário.
*
* Cada grafo referencia uma função que determina como devem ser
* desalocados os dados nele contidos.
*
* Esta função é chamada antes de se desalocar um vértice
* de um grafo.



***************************************************************************/
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

typedef enum {

         	GRA_CondRetOK ,
               /* Concluiu corretamente */
		 GRA_CondRetFaltouMemoria ,
		      /* Não há memória pra alocar */
        	 GRA_CondRetGrafoVazio ,
               /* o grafo não contém elementos */
		 GRA_CondRetArestaJaExiste,
	       /* A aresta já existe */		
		 GRA_CondRetNoNaoExiste,
	       /* O nó não existe */
		 GRA_CondRetArestaNaoExiste,
	       /* A aresta já existe */
   		GRA_CondRetJaEsta,
			/* Já está no nó */
		GRA_CondRetCaminhoExiste,
			/* Há caminho entre dois vértices */
		GRA_CondRetCaminhoNaoExiste
			/* Não há caminho entre os dois vértices */
   } GRA_tpCondRet ;

#ifdef _DEBUG
/* Declarações dos simbolos de instrumentação */
typedef enum
{
DeturpaTipoGrafo = 1,
/* Modifica o tipo do Grafo */
DeturpaTipoListaVertices = 2,
/* Modifica o tipo da Lista De vértices */
DeturpaTipoListaOrigens = 3,
/* Modifica o tipo da Lista de Origens */
DeturpaTipoIdCorrente = 4,
/* Modifica o tipo do Id corrente */
DeturpaPtGrafoNulo = 5,
/* Anula ponteiro do grafo */
DeturpaPtVerticesNulo = 6,
/* Anula ponteiro dos vértices do grafo */
DeturpaPtOrigensNulo = 7,
/* Anula ponteiro da lista de origens */
DeturpaIdCorrenteZero = 8,
/* Torna o id corrente zero */
DeturpaIdCorrenteNegativo =9
/* Torna o Id corrente Negativo */

} GRA_tpModoDeturpacao;
#endif
/***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico não dirigido vazio
*     Os possíveis tipos de elementos armazenados nos nós do grafo são desconhecidos a priori
*     Esta função inicializa as estruturas reguladoras do grafo
*
*  $EP Parâmetros
*	  refgrafo		- endereço ponteiro para a cabeça do grafo a ser gerado, a ser retornado por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo nó
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $EAE Assertivas de entrada
*	  refGrafo deve ser o endereço de uma variável do tipo 
*	  GRA_tppGrafo alocada pelo bloco usuário da função. 
*	  refGrafo deve ser, portanto, um ponteiro não nulo
*	  ExcluirValor é um ponteiro para uma função que tem a como objetivo excluir os
*	  valores que serão usados nos vértices do grafo
*	  Excluir valor não poder ser ponteiro nulo
*  $FV Valor retornado
*     Se executou corretamente retornará a GRA_CondRetOK
*     Se ocorreu alguma alocação de memória não conseguir ser realizada
*     a função retornará GRA_CondRetFaltouMemoria.
*  
*  $EAS Assertivas de saída
*	  Se a função operar corretamente, retornará GRA_CondRetOK
*	  e o valor da variável GRA_tppGrafo cujo endereço foi passado 
*	  à função receberá o Grafo criado
*	  Se ocorreu alguma alocação de memória não conseguir ser realizada
*	  A função retornará GRA_CondRetFaltouMemória e o valor de refGrafo
*	  não será modificado  
*
*
***********************************************************************/
GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo* refgrafo,  void   ( * ExcluirValor ) ( void * pDado ));

/***********************************************************************
*
*  $FC Função: GRA  &Destruir grafo
*
*  $ED Descrição da função
*     Esvazia o grafo recebido e destrói suas estruturas de controle.
*
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser destruido
*
* $EAE Assertivas de entrada
*	  grafo deve ser uma variável do tipo GRA_tppGrafo alocada pelo trecho
*	  usuário da função. 
*	  grafo deve conter um grafo gerado por esse módulo, i.e.
*	  pela função GRA_CriarGrafo;
*	  grafo deve ser, portanto, um ponteiro não nulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*    
*
* $EAS Assertivas de saída
*	
*	Se a função operar corretamente o retorno será GRA_CondRetOK
*	e o valor da vaiável GRA_tppGrafo passada continuará o mesmo,
*	porém, o grafo foi liberado da memória e não pode mais ser acessado
*	cabe ao trecho usuário da função atribuir null à variável após
*	o uso da função
*	
*    
*
***********************************************************************/


GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo grafo );

/***********************************************************************
*
*  $FC Função: GRA  &Inserir Nó
*
*  $ED Descrição da função
*     A função trata de inserir um novo nó no grafo, dando a ele um id único, pelo qual poderá ser 
*     identificado e operado posteriormente. Também o associará a uma informação qualquer, passada
*	  pelo parâmetro pInfo. Por definição um novo nó não tem arestas.
*	
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo 
*	  pInfo			- endereço a informação a ser armazenada no grafo
*	  pNoId			- endereço da variável que receberá o id do grafo criado, retornado por referência
*
*	$EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	  pInfo deve ser o endereço da informação, esta alocada pelo código usuário, que se quer
*	  adicionar em cada nó do grafo. 
*	  pInfo não pode ser nulo
*	  o tipo de pInfo deve ser o mesmo para todas as chamadas de GRA_InserirNo para um mesmo grafo
*	  pNoId deve ser um endereço de um inteiro alocado pelo código usuário
*	  pNoId não pode ser nulo.
*
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se Faltou memória em qualquer parte do processo, retornará GRA_CondRetFaltouMemoria
*
*  $EAE Assertivas de saída
*	Se a função executou corretamente retornará GRA_CondRetOK e
*	  o nó foi gerado, a informação associada a ele por pInfo está 
*	  corretamente colocada, e a variável cujo endereço foi passado no
*	  parâmetro pNoId recebeu o valor inteiro de identificação daquele nó
*	  recém criado, pelo qual o nó poderá ser acessado pelas funções de acesso
*	  e o nó corrente do grafo passou a ser o o nó gerado.
*	Se faltou memória em qualquer parte do processo, retornará GRA_CondRetFaltouMemoria e
*	  o no corrente do grafo continuará no estado anterior à chamada da função,
*	  o nó não é adicionado no grafo, e os parâmetros passados não sofrem alteração.
*
*     
***********************************************************************/
GRA_tpCondRet   GRA_InserirNo ( GRA_tppGrafo grafo, void * pInfo,int* pNoId);

/***********************************************************************
*
*  $FC Função: GRA  &Excluir Nó
*
*  $ED Descrição da função
*     A função recebe um grafo o id do nó a ser excluído do respectivo grafo.
*     o nó corrente passa a ser outro qualquer 
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo
*	  Id			- id do no a ser excluido
*  $EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	  Id deve ser um valor inteiro de identificação de um nó que exista no grafo
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se o no nao existir retornará GRA_CondRetNoNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*
*  $EAS Assertivas de saída
*	Se executou corretamente retornará GRA_CondRetOK e
*     o nó foi excluído corretamente, seu id não acessa nenhum nó.
*	  Se o grafo, após a exclusão, tiver ficado vazio, o nó corrente
*	   assumirá o estado nulo( não há corrente)
*	  caso contrário,
*	   o nó corrente será outro qualquer determinado arbitrariamente
*	Se o no nao existir retornará GRA_CondRetNoNaoExiste e
*	  o estado do grafo permanece o mesmo, o grafo não é modificado.
*	Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio e
*	  o estado do grafo permanece o mesmo, o grafo não é modificado.
***********************************************************************/

GRA_tpCondRet   GRA_ExcluirNo ( GRA_tppGrafo grafo, int Id);

/***********************************************************************
*
*  $FC Função: GRA  &Excluir Nó Corrente
*
*  $ED Descrição da função
*     A função exclui o no corrente do grafo. 
*		O no corrente passa a ser outro qualquer.
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo
*	$EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	   o grafo deve ter um nó corrente
*	  (A função é capaz de tratar grafos vazios, mas não é 
*	  o uso da função)
*	 
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*  $EAS Assertivas de saída
*	Se executou corretamente retornará GRA_CondRetOK e
*     o nó foi excluído corretamente, o id do nó corrente não acessa nenhum nó.
*	  Se o grafo, após a exclusão, tiver ficado vazio, o nó corrente
*	   assumirá o estado nulo( não há corrente)
*	  caso contrário,
*	   o nó corrente será outro qualquer determinado arbitrariamente
*	Se o no corrente nao existir retornará GRA_CondRetNoNaoExiste e
*	  o estado do grafo permanece o mesmo, o grafo não é modificado.
*	Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio e
*	  o estado do grafo permanece o mesmo, o grafo não é modificado.
*     
***********************************************************************/

GRA_tpCondRet   GRA_ExcluirNoCorrente ( GRA_tppGrafo grafo);

/***********************************************************************
*
*  $FC Função: GRA  &Inserir aresta
*
*  $ED Descrição da função
*     A função insere uma nova aresta entre os nós cujos Id foram passados como parâmetro. Por definição
*	  toda aresta que liga o nó A ao B, liga o nó B ao A também. 
*
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo no qual a aresta será inserida
*	  no_x_Id		- ID de um dos vértices onde será colocada a aresta
*	  no_y_Id		- ID do outro vértice onde será colocada a aresta
*	  idAresta		- Inteiro a ser adicionado à aresta 
*
*  $EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	  (A função é capaz de tratar grafos vazios, mas não é 
*	  o uso da função)
*     no_x_Id e no_y_Id devem ambos serem  identificadores de vértices válidos, i.e,
*	  pertencentes ao grafo.
*	  (A função é capaz de tratar se os nós forem inexistentes, mas não é 
*	  o uso da função)
*     idAresta deve ser um inteiro qualquer, que será adicionado à aresta.
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta já existe, retorna GRA_CondRetArestaJaExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*	  Se faltou memória para as arestas, retorna GRA_CondRetFaltouMemoria	
*  $EAS Assertivas de saída
*	Se executou corretamente retorna GRA_CondRetOK e
*	  o grafo terá uma nova aresta entre os dois vértices indicados
*	  por no_x_Id e no_y_Id cujo valor foi é o recebido no parâmetro
*	  idAresta.
*	Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste e
*     o grafo não é modificado.
*   Se a aresta já existe, retorna GRA_CondRetArestaJaExiste e
*     o grafo não é modificado
*	Se o grafo estiver vazio retorna GRA_CondRetGrafoVazio
*	  o grafo não é modificado
*	Se faltou memória para as arestas, retorna GRA_CondRetFaltouMemoria e
*     o grafo não é modificado   
*
***********************************************************************/

GRA_tpCondRet  GRA_InserirAresta( GRA_tppGrafo grafo, int no_x_Id, int no_y_Id, int idAresta);


/***********************************************************************
*
*  $FC Função: GRA  &Excluir aresta
*
*  $ED Descrição da função
*     A função exclui uma aresta existente entre os nós cujos Id foram passados como parâmetros.
*	  
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo cuja aresta será destruida
*	  no_x_Id		- ID de um dos vértices cuja aresta será destruída
*	  no_y_Id		- ID do outro vértice cuja aresta será destruída
*  $EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	  (A função é capaz de tratar grafos vazios, mas não é 
*	  o uso da função)
*     no_x_Id e no_y_Id devem ambos serem  identificadores de vértices válidos, i.e,
*	  pertencentes ao grafo.
*	  (A função é capaz de tratar se os nós forem inexistentes, mas não é 
*	  o uso da função)
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta não existe, retorna GRA_CondRetArestaNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*
*  $EAS Assertivas de saída
*	Se executou corretamente retorna GRA_CondRetOK e
*	  a aresta entre no_x_Id e no_y_Id será eliminada
*	  do grafo. o No corrente permanece no estado anterior.
*	Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste e
*     o grafo não é modificado.
*   Se a aresta Não existe, retorna GRA_CondRetArestaNãoExiste e
*     o grafo não é modificado
*	Se o grafo estiver vazio retorna GRA_CondRetGrafoVazio
*	  o grafo não é modificado
*
*
***********************************************************************/
GRA_tpCondRet  GRA_ExcluirAresta (GRA_tppGrafo grafo, int no_x_Id, int no_y_Id);

/***********************************************************************
*
*  $FC Função: GRA  &Obter Id Aresta
*
*  $ED Descrição da função
*     A função obtem o Id de uma aresta existente entre os nós cujos Id foram passados como parâmetros.
*	  
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo cuja aresta será destruida
*	  no_x_Id		- ID de um dos vértices cuja aresta será destruída
*	  no_y_Id		- ID do outro vértice cuja aresta será destruída
*	  pId			- ponteiro para inteiro para retornar o valor por referência
*
*	$EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	  (A função é capaz de tratar se os nós forem inexistentes, mas não é 
*	  o uso da função)
*     no_x_Id e no_y_Id devem ambos serem  identificadores de vértices válidos, i.e,
*	  pertencentes ao grafo.
*	  pId deve ser o endereçode uma variável inteira alocada pelo código usuário da função
*  $FV Valor retornado
*     Se executou corretamente retorna GRA_CondRetOK
*	  Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste
*	  Se a aresta não existe, retorna GRA_CondRetArestaNaoExiste
*	  Se o grafo estiver vazio retornará GRA_CondRetGrafoVazio
*  $EAS Assertivas de saída
*	Se executou corretamente retorna GRA_CondRetOK e
*	  o valor armazenada na aresta entre no_x_Id e no_y_Id do grafo
*	  será retornado por referência, para o endereço da variável inteira
*	  recebido pelo o parâmetro pId
*	Se um dos nós nao existe, retorna GRA_CondRetNoNaoExiste e
*     o grafo não é modificado.
*	  o valor da variável cujo endereço é passado
*	  ao parâmetro pId não se altera 
*   Se a aresta Não existe, retorna GRA_CondRetArestaNãoExiste e
*     o grafo não é modificado
*	  o valor da variável cujo endereço é passado
*	  ao parâmetro pId não se altera 
*	Se o grafo estiver vazio retorna GRA_CondRetGrafoVazio
*	  o grafo não é modificado
*     o valor da variável cujo endereço é passado
*	  ao parâmetro pId não se altera     
*
***********************************************************************/
GRA_tpCondRet  GRA_ObterIdAresta (GRA_tppGrafo grafo, int no_x_Id, int no_y_Id, int * pId);

/***********************************************************************
*
*  $FC Função: GRA  &Esvaziar Grafo
*
*  $ED Descrição da função
*     Esta Função esvazia o grafo, liberando todos os elementos. O grafo fica como se
*	  tivesse sido recém criado.
*	
*  $EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser esvaziado
*	 
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*	  Se o grafo já estava vazio, retorna GRA_CondRetGrafoVazio
*  $EAS Assertivas de saída
*	Se executou corretamente retornará GRA_CondRetOK e
*	 o grafo terá sido esvaziado, retornando ao estado original da estrutura.
*	 o seus nós, as arestas de cada nó terão sido liberados da memória
*	 o vértice corrente vai para o estado nulo(Não há nenhum)
*	Se o grafo já estava vazio, retorna GRA_CondRetGrafoVazio
*	 o grafo não é modificado
*     
***********************************************************************/

GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo grafo );

/***********************************************************************
*
*  $FC Função: GRA  &Imprimir Grafo
*
*  $ED Descrição da função
*     Esta Função para cada vértice do grafo recebido exibirá seu id
*	  e o conjunto dos ids dos vértices adjacentes a esse		
*  $EP Parâmetros
*	  grafo			- ponteiro para a cabeça do grafo a ser impresso
*	
*  $EAE Assertivas de entrada
*	  grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*     grafo deve ser, portanto, ponteiro não nulo. 
*	  grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*  $FV Valor retornado
*     Se executou corretamente retornará GRA_CondRetOK
*     Se o grafo está vazio, retornará GRA_CondRetGrafoVazio
* $EAS Assertivas de saída
*	Se executou corretamente retornará GRA_CondRetOK e
*	 o grafo terá sido impresso no monitor, Cada id de vertice
*	 exibirá um conjunto de ids, que são os ids dos vértices 
*	 adjacentes
*	Se o grafo já estava vazio, retorna GRA_CondRetGrafoVazio
*	 o grafo não é modificado. 
*	 Nada é exibido na tela.
*     
***********************************************************************/
GRA_tpCondRet  GRA_ImprimirGrafo(GRA_tppGrafo grafo);

/***********************************************************************
*
* $FC Função: GRA &Obter Valor do Nó Corrente
*
* $ED Descrição da função
* 	Esta Função transmite ao ponteiro cujo endereço é recebido
*   a informação do nó corrente. Este passa a apontar 
*	para essa informação.
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	pInfo - o endereço do ponteiro que receberá o nó
* $EAE Assertivas de entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo trecho de código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio
*	(A função é capaz de tratar se o grafo é vazio, mas não é o uso dela)
*	o grafo precisa ter um nó corrente
*	pInfo deve ser o endereço de um ponteiro slocado pelo código usuário da função
*	pInfo, portanto, não pode ser nulo
*	pInfo deve ser um endereço de ponteiro para o tipo de dados associado ao grafo
*	na sua criação, i.e. , deve ser do mesmo tipo que as informações armazenadas
*	no grafo
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* $EAS Assertivas de saída
*   Se executou corretamente retornará GRA_CondRetOK e
*	 pInfo apontará para a informação armazenada no nó corrente
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio e
*	o valor de pInfo não será modificado. 
*
***********************************************************************/

GRA_tpCondRet GRA_ObterValorNoCorrente(GRA_tppGrafo grafo, void ** pInfo);

/***********************************************************************
*
* $FC Função: GRA &Obter Nó Corrente
*
* $ED Descrição da função
* 	Esta Função recebe um grafo e retorna por ref o Id 
*	do nó corrente, pelo qual ele poderá ser acessado e operado.
*
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	refId - o endereço da variável que receberá o valor do id do nó
* $EAE Assertivas de entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo
*	(A função é capaz de tratar se o grafo é vazio, mas não é 
*	  o uso da função)
*	o grafo precisa ter um nó corrente
*	refId deve ser um endereço de uma variável alocada pelo código usuário.
*	Não pode, portanto, ser ponteiro nulo
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*
* $EAS Assertivas de Saída
*	Se executou corretamente retornará GRA_CondRetOK e
*	  o valor da variável cujo endereço foi passado ao parâmetro
*	  refId receberá o id do nó corrente do grafo
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio e
*	  o valor recebido por referência no parâmetro refId será 0.
*
***********************************************************************/
GRA_tpCondRet GRA_ObterNoCorrente( GRA_tppGrafo grafo, int * refId);

/***********************************************************************
*
* $FC Função: GRA &Ir nó vizinho
*
* $ED Descrição da função
* 	Esta função recebe o iD do nó vizinho para onde se deseja mudar o nó corrente
*	A função verifica se o id informado é adjacente ao corrente e só muda se for. 
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noVizinho - inteiro para o Id do nó que se deseja ir
* $EAE Assertivas de entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio
*(A função é capaz de tratar se o grafo é vazio, mas não é 
*	  o uso da função)
*	o grafo precisa ter um nó corrente
*	noId deve ser um inteiro cujo valor seja um id de um vértice
*	adjacente ao vértice corrente do grafo
* $FV Valor retornado
* 	Se executou corretamente retorna GRA_CondRetOK 
*	Se o grafo for vazio retorna GRA_CondRetGrafoVazio.
*	Se o nó não existir retorna GRA_CondRetNoNaoExiste.
*	Se não houver aresta entre os nós retorna GRA_CondRetArestaNaoExiste.
* $AES Assertivas de saída
* 	Se executou corretamente retorna GRA_CondRetOK e
*    o no corrente do grafo será o nó cujo o id foi recebido
*	 pelo parâmetro id vizinho
* 	Se o grafo for vazio retorna GRA_CondRetGrafoVazio.
*	 O grafo não é modificado
* 	Se o nó não existir retorna GRA_CondRetNoNaoExiste.
*	 O nó corrente permanece no estado anterior.
*	Se não houver aresta entre os nós retorna GRA_CondRetArestaNaoExiste.
*	 Significa que o nó informado não é vizinho do corrente.
*	 O nó corrente permanece no seu estado anterior
*   Se o nó desejado já for o corrente retorna GRA_CondRetJaEsta
*	 Significa que o id informado é o mesmo do corrente.
*	 o nó corrente permanece no seu estado anterior
*
*
***********************************************************************/

GRA_tpCondRet GRA_IrNoVizinho( GRA_tppGrafo grafo, int noVizinho);
/***********************************************************************
*
* $FC Função: GRA &Obter Valor do Nó
*
* $ED Descrição da função
* 	Esta Função recebe um id do vértice e faz o ponteiro cujo endereço 
* 	é recebido apontar para a informação do nó.
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noId - inteiro para o Id do nó cujo valor será recebido
* 	endVar - o endereço do ponteiro que receberá o nó
* $EAE Assertivas de Entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio
*	o grafo precisa ter um nó corrente
*	noId precisa conter um Id válido, i.e., um id de um vértice
*	contido no grafo.
*	endVar precisa ser o endereço de um ponteiro que receberá a informação do nó
*	o ponteiro cujo endereço é recebido por endVar deve ser do mesmo tipo  que a informação
*	armazenada no grafo.
*   A função Sabe Tratar exceções de grafoVazio e noNaoExistente, mas não cumprirá seu propósito
*	endVar não poder ser ponteiro nulo
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* 	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
* $EAS Assertivas de Saída
*	Se executou corretamente retorna GRA_CondRetOK e
*	  o ponteiro cujo o endereço foi passado ao parâmetro endVar
*	  apontará para a informação associada ao nó cujo id foi informado
*	  ao parâmetro noId
*	Se o grafo for vazio retorna GRA_CondRetGrafoVazio e
*	  o valor do ponteiro cujo endereço foi recebido não será modificado
*	Se o nó não existir retornará GRA_CondRetNoNaoExiste e
*	  o valor do ponteiro cujo endereço foi recebido não será modificado
***********************************************************************/
GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar);

/***********************************************************************
*
* $FC Função: GRA &Ir Para Nó
*
* $ED Descrição da função
* 	Esta Função recebe um id do vértice e o situa o elemento corrente
* 	da estrutura.
* 	Caso o nó não exista, a função vai manter o valor corrente recebido
*
* $EP Parâmetros
* 	grafo - ponteiro para a cabeça do grafo a ser impresso
* 	noId - inteiro para o Id do nó que virará corrente
*
* $EAE Assertivas de Entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio*
*	noId precisa conter um Id válido, i.e., um Id de um vértice
*	contido no grafo.*
*	*A função Sabe Tratar exceções de grafoVazio e noNaoExistente, 
*	mas não cumprirá seu propósito
* $FV Valor retornado
* 	Se executou corretamente retornará GRA_CondRetOK.
* 	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
* 	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*
* $EAS Assertivas de Saída
*	Se executou corretamente retorna GRA_CondRetOK e
*	  o no corrente do grafo passa ser o no cujo id
*	  foi passado ao parâmetro noId
*	Se o grafo for vazio retorna GRA_CondRetGrafoVazio e
*	  o no corrente do grafo permanece no seu estado anterior.
*	Se o nó não existir retornará GRA_CondRetNoNaoExiste.
*	  o no corrente do grafo permanece no seu estado anterior.
***********************************************************************/
GRA_tpCondRet GRA_IrParaNo(GRA_tppGrafo grafo,int noId);


/***********************************************************************
*
* $FC Função: GRA &ObterVértices
*
* $ED Descrição da função
*	Esta função retorna um vetor com todos os ids dos vértices 
*	contidos no grafo no momento de sua execução
*	
* $EP Parâmetros
*	grafo - ponteiro para a cabeça do grafo a ser impresso
*	refPtrIds - endereço do ponteiro que receberá o vetor de ids
*	tam - endereço do inteiro que receberá o tamanho do vetor
* $EAE Assertivas de Entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio
*	refPtrIds deve ser o endereço de um ponteiro criado pelo código usuário.
*	refPtrIds não pode ser, portanto, nulo.
*	tam endereço e uma variável inteira alocada pelo código usuário
*	tam não pode ser, portanto, ponteiro nulo
* A função Sabe Tratar exceções de grafoVazio , mas não cumprirá seu propósito
* $FV Valor retornado
*	Se o procedimento for bem sucedido, retornará GRA_CondRetOK
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*	Se faltou memória retornará GRA_CondRetFaltouMemória
* $EAS Assertivas de Saída
*   Se o procedimento for bem sucedido, retornará GRA_CondRetOK
*	 o ponteiro cujo endereço foi passado pelo parâmetro refPtrIds
*	 receberá um vetor de inteiros (Todos os ids dos vértices que
*	 o grafo contém)e a variável cujo endereço foi informado ao parâmetro
*	 tam receberá o tamanho desse vetor.
*	Se o grafo for vazio retorna GRA_CondRetGrafoVazio e
*	 os valores das variáveis cujos endereços foram passados aos 
*	 parâmetros refPtrIds e tam permenacem inalterados.
*	Se faltou memória retorna GRA_CondRetFaltouMemoria e
*	 os valores das variáveis cujos endereços foram passados aos 
*	 parâmetros refPtrIds e tam permenacem inalterados.
*
***********************************************************************/
GRA_tpCondRet GRA_ObterVertices(GRA_tppGrafo grafo,int** refPtrIds,int *tam);
/***********************************************************************
*
* $FC Função: GRA &ObterArestasNo
*
* $ED Descrição da função
*	Esta função retorna um vetor com todos os ids dos vértices adjacentes 
*	ao vertice de noId informado.
*	
* $EP Parâmetros
*	grafo - ponteiro para a cabeça do grafo a ser impresso
*	noId - inteiro que é o id do nó cujas arestas serão obtidas
*	refPtrIds - endereço do ponteiro que receberá o vetor de ids
*	tam - endereço do inteiro que receberá o tamanho do vetor
* $EAE Assertivas de Entrada
*	grafo deve ser uma variável GRA_tppGrafo alocado pelo código usuário da função
*   grafo deve ser, portanto, ponteiro não nulo. 
*	grafo deve ser um grafo já alocado pela função GRA_CriarGrafo;
*	o grafo não pode ser vazio
*	noId deve conter um id válido, isto é , um id de um vértice presente
*	no grafo.
*	refPtrIds deve ser o endereço de um ponteiro criado pelo código usuário.
*	refPtrIds não pode ser, portanto, nulo.
*	tam endereço e uma variável inteira alocada pelo código usuário
*	tam não pode ser, portanto, ponteiro nulo
*   A função Sabe Tratar exceção de grafoVazio , mas não cumprirá seu propósito
* $FV Valor retornado
*	Se o procedimento for bem sucedido, retornará GRA_CondRetOK
*	Se o grafo for vazio retornará GRA_CondRetGrafoVazio.
*	Se faltou memória retornará GRA_CondRetFaltouMemória
* $EAS Assertivas de Saída
*   Se o procedimento for bem sucedido, retorna GRA_CondRetOK e
*	 o ponteiro cujo endereço foi passado pelo parâmetro refPtrIds
*	 receberá um vetor de inteiros (Todos os ids dos vértices que
*	 o adjacentes ao nó cujo id foi informado ao parâmetro noId )
*    e a variável cujo endereço foi informado ao parâmetro
*	 tam receberá o tamanho desse vetor.
*	Se o grafo for vazio retorna GRA_CondRetGrafoVazio e
*	 os valores das variáveis cujos endereços foram passados aos 
*	 parâmetros refPtrIds e tam permenacem inalterados.
*	Se faltou memória retorna GRA_CondRetFaltouMemoria e
*	 os valores das variáveis cujos endereços foram passados aos 
*	 parâmetros refPtrIds e tam permenacem inalterados.
***********************************************************************/
GRA_tpCondRet GRA_ObterArestasNo(GRA_tppGrafo grafo,int noId,int** refPtrIds,int *tam);