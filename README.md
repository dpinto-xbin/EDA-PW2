# EDA-PW2

### Autors: 
Diogo Pinto & Ricardo Cruz

# Course: EDA2



### Phase 2 - Objectives

<details>

<summary>1</summary>

# Definição de uma estrutura de dados dinâmica para representação da localização de um conjunto de clientes e meios de mobilidade elétrica, recorrendo a um grafo.

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

<summary>2.1</summary>

# Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados).
  
  Reading from a text file:
  
  We use fgets(), you can check on Pickups.c the region READ.

  

  Saving to a binary file:
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
This way the graph is saved with all nodes and edges.

</details>


<details>
  <summary>2.2</summary>
  
  # Dado a localização de um cliente, listar os meios de mobilidade elétrica de um determinado tipo existentes num determinado raio.
  
 Given the graph and the data we have, wich is latitude and longitude, we decided to use the **Haversine Formula**.
  This way we calculate the distance of two different points, the client location versus the pickup points locations.
  
  Here's the formula:
  
<img width="439" alt="27240436-e9a459da-52d4-11e7-8f84-f96d0b312859" src="https://github.com/dpinto-xbin/EDA-PW2/assets/90906538/ed93265a-7791-4012-9d54-03ecfc0eaf70">

  With **math.h** we are able to use the **Haversine Formula**.
  
  ```mermaid
flowchart TD
    A[Graph] -->B(Select node with latitude and longitude)
    B --> C{Haversine and if distance is <= 5km}
    C --> D[Node ID]
    C -->E[Location]
    C --> F[Distance]
```
  
  </details>



