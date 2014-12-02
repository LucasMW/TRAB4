GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar);

GRA_tpCondRet GRA_ObterValorNo(GRA_tppGrafo grafo, int noId,void** endVar)
{
	GRA_noGrafo no;
	if(LIS_IrInicioLista(grafo->pVertices)==LIS_CondRetListaVazia)
		return  GRA_CondRetGrafoVazio;
	do 
	{   no=(GRA_noGrafo)LIS_ObterValor(grafo->pVertices);
		if(no->verticeId==noId)
		{ /* Achou */
			*endVar=no->pInfo;
			return GRA_CondRetOK;
		}
	}while(LIS_AvancarElementoCorrente(grafo->pVertices,1)!=LIS_CondRetFimLista);
	/* Nao Achou */
	return GRA_CondRetNoNaoExiste;
}