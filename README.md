istema de Gerenciamento de Vendas em C

📄 Descrição do Projeto
Este é um sistema de gerenciamento de vendas desenvolvido em linguagem C. O programa permite registrar vendas de itens de vestuário, calcular totais com descontos, listar vendas por data e gerar relatórios financeiros simples, como o faturamento diário e a identificação dos itens mais e menos vendidos.

O objetivo do projeto é demonstrar o uso de estruturas (structs), manipulação de arquivos (leitura e escrita) e funções de ordenação (qsort) para criar uma aplicação funcional de console.

🚀 Funcionalidades
O programa oferece as seguintes opções no menu principal:

1. Registrar nova venda: Salva uma nova transação com detalhes como data, código do item, nome, marca, quantidade e preço.

2. Listar vendas por data: Exibe todas as vendas realizadas em uma data específica, ordenadas por valor total em ordem decrescente.

3. Faturamento bruto diário: Calcula e mostra a soma total de todas as vendas em uma data informada.

4. Quantidade de vendas por data: Conta e exibe o número de transações em um dia específico.

5. Item mais vendido: Identifica e mostra o item com a maior quantidade de unidades vendidas em um dia.

6. Item menos vendido: Identifica e mostra o item com a menor quantidade de unidades vendidas em um dia.

0. Sair: Encerra o programa.

⚙️ Como Compilar e Executar
Para compilar e executar este projeto, você precisará de um compilador C (como o GCC).

Clone o repositório:

Bash

git clone https://github.com/<Seu-Usuário>/<Seu-Repositorio>.git
cd <Seu-Repositorio>
Compile o código usando GCC:

Bash

gcc -o vendas main.c
Obs: O nome do arquivo fonte pode variar, ajuste se necessário (ex: gcc -o vendas programa_loja.c).

Execute o programa:

No Windows:

Bash

vendas.exe
No Linux/macOS:

Bash

./vendas
⚠️ Observações
O programa salva os dados em um arquivo binário chamado loja_roupa.txt.

Para que os caracteres especiais (acentuação) sejam exibidos corretamente no terminal, pode ser necessário configurar a codificação para UTF-8. No Windows, você pode usar o comando chcp 65001 no terminal antes de executar o programa.
