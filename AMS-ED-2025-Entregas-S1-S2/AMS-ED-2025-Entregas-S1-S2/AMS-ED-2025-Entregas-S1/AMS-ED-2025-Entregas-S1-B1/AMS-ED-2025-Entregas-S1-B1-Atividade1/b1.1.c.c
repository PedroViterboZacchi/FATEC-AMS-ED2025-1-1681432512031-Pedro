#include <stdio.h>

void AplicarDesconto(float *Preco, float Desconto) {
    *Preco = *Preco - Desconto;
}
    
    int main() {
        float precoProduto, Desconto;
        
        printf ("Digite o preço do produto: R$");
        scanf ("%f", &precoProduto);
        
        printf ("Digite o valor do desconto: R$");
        scanf ("%f", &Desconto);
        
        printf("\nPreco original: R$ %.2f\n", precoProduto);
        
        AplicarDesconto (&precoProduto, Desconto);
        
        printf("\nDesconto aplicado: R$ %.2f\n", Desconto);
        printf("\nValor final: R$ %.2f\n", precoProduto);
        
        return 0;
    }



