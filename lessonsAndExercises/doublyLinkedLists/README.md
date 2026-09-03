# Aula 6a - Listas Duplamente Encadeadas

## Exercícios

1. Por que a lista duplamente encadeada precisa de duas atualizações extras em inserirInicio (o ant do antigo início, e possivelmente l->fim), que não existiam na versão simplesmente encadeada?

2. Explique por que inserirFim passa a ser O(1) na lista duplamente encadeada, mesmo sem alterar em nada a forma como buscar ou removerPorCod localizam um nodo pelo código.

3. Na função removerPorCod, por que é necessário tratar separadamente os casos em que o nodo removido é o início (aux->ant == NULL) ou o fim (aux->prox == NULL) da lista?

4. Se um nodo estiver "sozinho" na lista (é ao mesmo tempo o início e o fim), o que deve acontecer com l->ini e l->fim ao removê-lo? Verifique se o código de removerPorCod apresentado trata esse caso corretamente.

5. Cite uma situação prática em que ser capaz de percorrer uma lista "de trás para frente" (com imprimirInverso) é útil.

6. Implemente uma função int inserirAntes(ListaDuplaEnc *l, int cod, Produto prod) que insira prod imediatamente antes do nodo cujo código é cod, retornando 1 em caso de sucesso ou 0 caso o código não seja encontrado. Dica: use o ponteiro ant do nodo encontrado para "encaixar" o novo nodo entre os dois.

## Respostas

1. Como cada nodo, em uma lista duplamente encadeada, contem ponteiros para o próximo nodo e para o nodo anterior, precisamos estabelecer que o anterior do antigo primeiro nodo (caso ele exista) seja o novo nodo. Caso a lista seja vazia (não existe um nodo inicial nem final), devemos definir o nodo criado como o inicio e final da lista.

2. Pois agora a estrutura Lista Duplamente Encadeada contém um ponteiro para o fim da lista. Ou seja, inserirFim não depende de buscar nada — ela só precisa saber onde está o último nodo, e isso já está disponível diretamente em l->fim, sem percorrer a lista. Já buscar e removerPorCod continuam precisando localizar um nodo específico pelo seu código, o que exige examinar os nodos um a um até encontrar (ou não) o código procurado — os ponteiros extras não ajudam nesse tipo de busca por conteúdo, apenas no acesso direto às duas pontas da lista.

3. Pois é necessário atualizar os ponteiros ini e fim da estrtura Lista Duplamete Encadeada.

    Porque o nodo do início não possui antecessor (aux->ant == NULL), então não há um aux->ant->prox válido para atualizar — nesse caso, é a própria struct da lista (l->ini) que precisa passar a apontar para o novo início. Da mesma forma, o nodo do fim não possui sucessor (aux->prox == NULL), então é l->fim quem precisa ser atualizado diretamente. Sem esses casos especiais, o código tentaria acessar campos de um ponteiro NULL.

4. l->ini e l->fim serão NULL. A função removerPorCod trata corretamente esse caso, fazendo que o ínicio e o fim da lista sejam NULL e liberando o espaço da memória ocupado pelo nodo excluído.

5. Um exemplo é o histórico de navegação de um navegador: os botões "voltar" e "avançar" precisam se mover pela sequência de páginas visitadas nos dois sentidos — algo natural de implementar com uma lista duplamente encadeada, em que a página atual é um nodo, e "voltar"/"avançar" apenas seguem ant/prox.

6. Função "insertBefore()" implementada no arquivo "doublyLinkedList.c" e testada no arquivo "main.c". 