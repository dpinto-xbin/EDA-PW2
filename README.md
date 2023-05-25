# EDA-PW2

PRATICAL WORK PHASE 2

<details>

<summary>First Point</summary>

### "Definição de uma estrutura de dados dinâmica para representação da localização de um conjunto de clientes e meios de mobilidade elétrica, recorrendo a um grafo;"

Our approach:

  ![STRUCT GRAPH](https://github.com/dpinto-xbin/EDA-PW2/assets/90906538/29a14f25-1e4d-4728-8e9a-e1461d20ae90)
  
  
| Nodes  | Heads |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |



</details>

<details>

<summary>Second Point</summary>

### "Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados)."  
  

```
void writeNodeToFile(Node* nodes_head) {
    FILE* file = fopen("nodes.bin", "wb");
    Node* current = nodes_head;
    while (current != NULL) {
        fwrite(current, sizeof(Node), 1, file);
        current = current->next;
    }
    fclose(file);
}
```


</details>



