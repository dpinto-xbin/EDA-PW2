# EDA-PW2

PRATICAL WORK PHASE 2

<details>

<summary>First Point</summary>

### "Definição de uma estrutura de dados dinâmica para representação da localização de um conjunto de clientes e meios de mobilidade elétrica, recorrendo a um grafo;"

Our approach:

  ![STRUCT GRAPH](https://github.com/dpinto-xbin/EDA-PW2/assets/90906538/29a14f25-1e4d-4728-8e9a-e1461d20ae90)
  
  
| Nodes  | Latitude | Longitude |
| ------------- | ------------- | ------------- |
| A  | 41.536719  | -8.627301  |
| B  | 41.537748  | -8.622770  |
| C  | 41.537628  | -8.621906  |
| D  | 41.531540  | -8.618960  |
| E  | 41.452470  | -8.562170  |
| F  | 41.494751  | -8.644610  |

  ### Non-oriented graph with weights (distance)
![GRAPH](https://github.com/dpinto-xbin/EDA-PW2/assets/90906538/1cf5e227-786d-46a6-b7cf-ff8eb017ebb3)


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



