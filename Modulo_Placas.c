#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<conio.h>
int count_lines = 0;
int num_dados = 0;

typedef struct help
{
    char *dado;
} help;

typedef struct pessoa
{
    char nome[50];
    char cpf[15];
    char carro[50];
    char categoria_carro[15];
    char placa_carro[10];
    int prioridade;
} pessoa;

typedef struct lista
{
    int qtd;
    struct no *inicio;
} lista;

typedef struct no
{
    char nome[50];
    char cpf[15];
    char carro[50];
    char categoria_carro[15];
    char placa_carro[10];
    int prioridade;
    struct no *prox;
} no;

help * aloca_help();
pessoa * aloca_pessoa();
lista * aloca_lista();
no * aloca_no(pessoa a);
int login();
pessoa * le_arquivo();
pessoa * ordena_prioridade(help *aux);
void * menu(pessoa *sociedade);
void * menu_admin(pessoa *sociedade);
int busca_categoria(pessoa *sociedade, int categoria);
lista * chamada(pessoa *sociedade, int n);
pessoa remover(pessoa *sociedade);
void limpar_folha(pessoa *sociedade);
void mostrar_convocados(no *aux);
int busca_veiculo(char *placa, pessoa *sociedade);
int busca_veiculo_chamado(char *placa);
int busca_veiculo_cpf(char *cpf, pessoa * sociedade);
int busca_veiculo_cpf_chamado(char *cpf);
void relatorio(pessoa *sociedade);
void adicionar_login();
pessoa * administracao_base_dados(pessoa * sociedade);
void inserir_proprietario(pessoa *sociedade);
void escrever_arq(lista *a);
void sobrescrever_arq(pessoa *sociedade);


int main()
{
    setlocale(LC_ALL, "Portuguese");

    int op = 0, ret = 0;

    do
    {
        printf("\t\t\t");
        printf(">>> SEJA BEM VINDO AO M�DULO DE TROCA DE PLACAS DO DETRAN-DF <<<\n\n\t|FA�A SEU LOGIN DE ACORDO COM AS INFORMA��ES ENTREGUES PREVIAMENTE PELA EQUIPE DE INFORM�TICA|\n");
        printf("\t|OBS.: CASO N�O POSSUA O SEU LOGIN, CONTACTE O ADMINISTRADOR\t\t\t\t     |\n\n");
        printf(">>> OP��ES <<<\n\n1 - LOGIN\n2 - FECHAR O PROGRAMA\n");
        printf("\nDIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            ret = 0;
            ret = login();//Efetua o login
            if(ret == 1)//Se 1: entra no menu dos agentes passando a struct pessoa que ser� retornada pela fun��o le_arquivo()
            {
                menu(le_arquivo());
            }
            else if(ret == 2)//Se 2: entra no menu dos administradores passando a struct pessoa que ser� retornada pela fun��o le_arquivo()
            {
                menu_admin(le_arquivo());
            }
            else if(ret == 3)//Se 3: � o retorno de quem n�o fez o login ou por n�o ter um ou por ter optado por n�o fazer o login
            {

            }
            break;
        case 2://Sa�da total do programa
            printf("\nSAINDO!\n\n");
            break;
        default:
            printf("\nOP��O INV�LIDA!\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(op != 2);

    return 0;
}

help * aloca_help()
{
    help *novo;
    int i;

    novo = (help*) malloc(sizeof(help)*count_lines);

    for(i=0; i<count_lines; i++)
    {
        novo[i].dado = (char*) malloc(sizeof(char)*50);
    }

    return novo;
}

pessoa * aloca_pessoa()
{
    pessoa *novo;
    int i;

    novo = (pessoa*) malloc(sizeof(pessoa)*num_dados);

    for(i=1; i<num_dados; i++)
    {
        novo[i].prioridade = 0;
    }

    return novo;
}

lista * aloca_lista()
{
    lista *novo;

    novo = (lista*) malloc(sizeof(lista));

    novo->qtd = 0;
    novo->inicio = NULL;

    return novo;
}

no * aloca_no(pessoa a)
{
    no *novo;
    novo = (no*) malloc(sizeof(no));

    //Aloca e j� atribui os dados no n�

    novo->prioridade = 0;
    novo->prox = NULL;

    strcpy(novo->nome, a.nome);
    strcpy(novo->cpf, a.cpf);
    strcpy(novo->carro, a.carro);
    strcpy(novo->categoria_carro, a.categoria_carro);
    strcpy(novo->placa_carro, a.placa_carro);
    novo->prioridade = a.prioridade;

    if(stricmp(novo->categoria_carro, "Aprendizagem") == 0)
    {
        strcpy(novo->categoria_carro, "Especial");
    }
    else if(stricmp(novo->categoria_carro, "Aluguel") == 0)
    {
        strcpy(novo->categoria_carro, "Comercial");
    }
    else if(stricmp(novo->categoria_carro, "Experiencia") == 0)
    {
        strcpy(novo->categoria_carro, "Especial");
    }
    else if(stricmp(novo->categoria_carro, "Colecao") == 0)
    {
        strcpy(novo->categoria_carro, "Colecionador");
    }

    if(novo->placa_carro[4] == '0')
    {
        novo->placa_carro[4] = 'A';
    }
    if(novo->placa_carro[4] == '1')
    {
        novo->placa_carro[4] = 'B';
    }
    if(novo->placa_carro[4] == '2')
    {
        novo->placa_carro[4] = 'C';
    }
    if(novo->placa_carro[4] == '3')
    {
        novo->placa_carro[4] = 'D';
    }
    if(novo->placa_carro[4] == '4')
    {
        novo->placa_carro[4] = 'E';
    }
    if(novo->placa_carro[4] == '5')
    {
        novo->placa_carro[4] = 'F';
    }
    if(novo->placa_carro[4] == '6')
    {
        novo->placa_carro[4] = 'G';
    }
    if(novo->placa_carro[4] == '7')
    {
        novo->placa_carro[4] = 'H';
    }
    if(novo->placa_carro[4] == '8')
    {
        novo->placa_carro[4] = 'I';
    }
    if(novo->placa_carro[4] == '9')
    {
        novo->placa_carro[4] = 'J';
    }

    return novo;
}

int login()
{
    FILE *arq;
    char login[50];
    char senha[7];
    char l[50];
    char s[10];
    int op = 0;
    int i;

    do
    {
        system("cls");

        printf("\t\t\t>>> OP��ES DE LOGIN <<<\n\t|1 - AGENTE: � O USU�RIO QUE IR� ATENDER DIRETAMENTE O P�BLICO.|");
        printf("\n\t|2 - ADMINISTRADOR: � O GERENTE DE TODO O PROCESSO DE TROCA.   |");
        printf("\n\n\n>>> OP��ES <<<\n\n1 - LOGIN AGENTE\n2 - LOGIN ADMINISTRADOR\n");
        printf("3 - SAIR\n\n");
        printf("DIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1://Se op��o 1: efetua login do agente
            printf("\nDIGITE SEU LOGIN: ");
            fflush(stdin);
            gets(login);

            printf("DIGITE SUA SENHA: ");
            for(i=0; i<6; i++)//Recebe senha do usu�rio mostrando na tela apenas *
            {
                senha[i] = getch();
                putchar('*');
            }
            senha[i] = '\0';

            arq = fopen("login_agente.txt", "r");

            while(!feof(arq))//Verifica se o login e a senha informados est�o corretos de acordo com a base de dados de login dos agentes
            {
                fgets(l, 50, arq);
                fgets(s, 10, arq);
                l[strlen(l)-1] = '\0';
                s[strlen(s)-1] = '\0';
                if(strcmp(login, l)==0 && strcmp(senha, s)==0)//Login e senha s�o verificados em conjunto
                {
                    fclose(arq);
                    return 1;//Retorna 1 se o login e a senha estiverem corretos
                }
            }

            printf("\n\nLOGIN E/OU SENHA INCORRETOS, TENTE NOVAMENTE!\n\n");
            fclose(arq);

            break;

        case 2://Se op��o 2: efetua login do administrador
            arq = fopen("login_admin.txt", "r");

            printf("\nDIGITE SEU LOGIN: ");
            fflush(stdin);
            gets(login);

            printf("DIGITE SUA SENHA: ");
            for(i=0; i<6; i++)//Recebe senha do usu�rio mostrando na tela apenas *
            {
                senha[i] = getch();
                putchar('*');
            }
            senha[i] = '\0';

            while(!feof(arq))//Verifica se o login e a senha informados est�o corretos de acordo com a base de dados de login dos administradores
            {
                fgets(l, 50, arq);
                fgets(s, 10, arq);
                l[strlen(l)-1] = '\0';
                s[strlen(s)-1] = '\0';
                if(strcmp(login, l)==0 && strcmp(senha, s)==0)//Login e senha s�o verificados em conjunto
                {
                    fclose(arq);
                    return 2;//Retorna 2 se o login e a senha estiverem corretos
                }
            }

            fclose(arq);
            printf("\n\nLOGIN E/OU SENHA INCORRETOS, TENTE NOVAMENTE!\n\n");

            break;

        case 3://Se op��o 3: retorna diretamente sem fazer login para a tela inicial
            printf("\n");
            return 3;
            break;
        default:
            printf("\nOP��O INV�LIDA\n\n");
            break;
        }
        system("pause");
    }
    while(op != 3);

    return 0;
}

pessoa * le_arquivo()
{
    pessoa *novo;
    FILE *arq;
    help *aux;
    int i;
    char a[50];

    count_lines = 0;

    arq = fopen("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt", "r");
    if(arq == NULL)
    {
        printf("\nERRO NA ABERTURA DO ARQUIVO.\n");
    }

    while(!feof(arq))//Conta quantas linhas tem o arquivo
    {
        fgets(a, 50, arq);
        count_lines++;
    }
    count_lines--;//Retira uma linha porque a �ltima linha, que cont�m apenas um '\n' tamb�m � contabilizada
    fclose(arq);//Fecha o arquivo para abrir novamente logo em seguida para reiniciar o 'feof'

    num_dados = count_lines / 5 + 1;

    arq = fopen("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt", "r");

    aux = aloca_help();//Help: struct auxiliar apenas para guardar todos os dados do arquivo de uma vez

    for(i=0; i<count_lines; i++)//Guarda todos os dados do arquivo
    {
        fgets(aux[i].dado, 50, arq);
        aux[i].dado[strcspn(aux[i].dado, "\n")] = 0;
    }

    novo = ordena_prioridade(aux);//Passa a struct help como par�metro para ordenar como uma fila de prioridade pela estrutura heap

    free(aux);
    fclose(arq);

    return novo;
}

pessoa * ordena_prioridade(help *aux)
{
    pessoa *sociedade;
    pessoa aux_pessoa;
    int pai = 0;
    int filho = 0;
    int k = 0;
    int i;

    sociedade = aloca_pessoa();//Aloca struct pessoa que contem 5 dados

    sociedade[0].prioridade = 7;//Coloca a prioridade da posi��o 0 como 7 para barrar as outras prioridades que cont�m valor menor que 7

    for(i=1; i<num_dados; i++)
    {
        strcpy(sociedade[i].nome, aux[k].dado);//Come�a a alocar os dados da posi��o i na struct pessoa
        k++;
        strcpy(sociedade[i].cpf, aux[k].dado);
        k++;
        strcpy(sociedade[i].carro, aux[k].dado);
        k++;
        strcpy(sociedade[i].categoria_carro, aux[k].dado);
        k++;
        strcpy(sociedade[i].placa_carro, aux[k].dado);//Termina de alocar os dados da posi��o i
        k++;

        if(stricmp(sociedade[i].categoria_carro, "Diplomatico") == 0)//Atribui prioridade da posi��o de acordo com a categoria
        {
            sociedade[i].prioridade = 1;
        }
        else if(stricmp(sociedade[i].categoria_carro, "Aprendizagem") == 0)
        {
            sociedade[i].prioridade = 2;
        }
        else if(stricmp(sociedade[i].categoria_carro, "Aluguel") == 0)
        {
            sociedade[i].prioridade = 3;
        }
        else if(stricmp(sociedade[i].categoria_carro, "Particular") == 0)
        {
            sociedade[i].prioridade = 4;
        }
        else if(stricmp(sociedade[i].categoria_carro, "Experiencia") == 0)
        {
            sociedade[i].prioridade = 5;
        }
        else if(stricmp(sociedade[i].categoria_carro, "Colecao") == 0)
        {
            sociedade[i].prioridade = 6;
        }

        if(i > 1)//Como a primeira posi��o n�o tem ningu�m para ser comparada, s� � feita a verifica��o de ordena��o a partir da segunda posi��o
        {
            filho = i;
            pai = filho/2;
            while(sociedade[pai].prioridade < sociedade[filho].prioridade)//Enquanto a posi��o filho for maior que a do pai, eles trocam de lugar
            {
                aux_pessoa = sociedade[pai];
                sociedade[pai] = sociedade[filho];
                sociedade[filho] = aux_pessoa;

                filho = pai;//O filho se torna o pai
                pai = filho/2;//� calculado o pai do novo filho e � feita a repeti��o caso a prioridade ainda esteja maior
            }
        }
    }

    return sociedade;
}

void * menu(pessoa *sociedade)
{
    int op = 0, ret = 0, n = 0, categoria = 0;
    char placa[9], cpf[15];
    int i;

    system("cls");

    do
    {
        printf("\t\t\t>>>BEM VINDO AO MENU AGENTE!<<<\n\n\n");
        printf("\n-> EM CASO DE D�VIDAS, ACIONE A OP��O AJUDA <-\n\n");
        printf("\t\t>>> OP��ES <<<\n");
        printf("\n\t|1 - BUSCA DE CATEGORIA                                  |");
        printf("\n\t|                                                        |");
        printf("\n\t|2 - BUSCAR SITUA��O DE VE�CULO PELA PLACA               |");
        printf("\n\t|                                                        |");
        printf("\n\t|3 - BUSCAR SITUA��O DE VE�CULO PELO CPF DO PROPRIET�RIO |");
        printf("\n\t|                                                        |");
        printf("\n\t|4 - INSERIR PROPRIET�RIO NA BASE DE DADOS               |");
        printf("\n\t|                                                        |");
        printf("\n\t|5 - AJUDA                                               |");
        printf("\n\t|                                                        |");
        printf("\n\t|6 - DESLOGAR                                            |");
        printf("\n\n\nDIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            do
            {
                system("cls");
                printf("\t\t    >>>OP��ES<<<\n");
                printf("\n\t\t|1 - DIPLOM�TICO  |");
                printf("\n\t\t|                 |");
                printf("\n\t\t|2 - APRENDIZAGEM |");
                printf("\n\t\t|                 |");
                printf("\n\t\t|3 - ALUGUEL      |");
                printf("\n\t\t|                 |");
                printf("\n\t\t|4 - PARTICULAR   |");
                printf("\n\t\t|                 |");
                printf("\n\t\t|5 - EXPERI�NCIA  |");
                printf("\n\t\t|                 |");
                printf("\n\t\t|6 - COLE��O      |\n");
                printf("\nDIGITE O N�MERO DA CATEGORIA QUE DESEJA BUSCAR: ");
                categoria = 0;
                fflush(stdin);
                scanf("%d", &categoria);

                if(categoria < 7)
                {
                    ret = busca_categoria(sociedade, categoria);//Busca a quantidade de placas que ainda faltam trocar para o padr�o MERCOSUL

                    if(ret == 0)
                    {
                        printf("\nOS VE�CULOS DA CATEGORIA INFORMADA J� TERMINARAM DE TROCAR AS PLACAS PARA O PADR�O MERCOSUL.\n\n");
                    }
                    else
                    {
                        printf("\nFALTAM %d VE�CULOS PARA TROCA DE PLACAS PARA O PADR�O MERCOSUL.\n\n", ret);
                    }
                }
                else
                {
                    printf("\nOP��O INV�LIDA!\n\n");
                    system("pause");
                }
            }
            while(categoria > 6);

            break;
        case 2:
            system("cls");
            printf("DIGITE A PLACA DO VE�CULO NO FORMATO AAA0000: ");
            placa[0] = '\0';
            fflush(stdin);
            scanf("%s", placa);

            ret = 0;
            ret = busca_veiculo(placa, sociedade);//Busca situa��o de um ve�culo espec�fica atrav�s da placa

            if(ret != 0)
            {
                printf("\nVE�CULO '%s' COM PLACA '%s' AINDA EM LISTA DE ESPERA PARA TROCA DE PLACAS.\n\n", sociedade[ret].carro, sociedade[ret].placa_carro);
            }
            else if(busca_veiculo_chamado(placa))
            {
                printf("\nVE�CULO COM PLACA '%s' J� INTIMADO PARA TROCA DE PLACAS.\n\n", placa);
            }
            else
            {
                printf("\nVE�CULO N�O CADASTRADO NA BASE DE DADOS\n\n");
            }
            break;
        case 3:
            system("cls");
            printf("DIGITE O CPF DO PROPRIET�RIO DO VE�CULO NO FORMATO 000.111.222-33: ");
            cpf[0] = '\0';
            fflush(stdin);
            scanf("%s", cpf);

            ret = 0;
            ret = busca_veiculo_cpf(cpf, sociedade);//Busca situa��o de um ve�culo espec�fica atrav�s do cpf

            if(ret != 0)
            {
                printf("\nVE�CULO '%s' COM PLACA '%s' AINDA EM LISTA DE ESPERA PARA TROCA DE PLACAS.\n\n", sociedade[ret].carro, sociedade[ret].placa_carro);
            }
            else if(busca_veiculo_cpf_chamado(cpf))
            {
                printf("\nPROPRIET�RIO J� INTIMADO PARA TROCA DE PLACAS.\n\n");
            }
            else
            {
                printf("\nPROPRIET�RIO N�O POSSUI NENHUM VE�CULO CADASTRADO NA BASE DE DADOS\n\n");
            }
            break;
        case 4:
            inserir_proprietario(sociedade);
            free(sociedade);
            sociedade = le_arquivo();
            break;
        case 5:
            system("cls");
            printf("\n\t\t|1 - BUSCA DE CATEGORIA: QUANTITATIVO DE VE�CULOS QUE AINDA NECESSITAM          |\n");
            printf("\t\t|    TROCAR AS PLACAS PARA O NOVO MODELO MERCOSUL                               |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|2 - BUSCAR SITUA��O DE VE�CULO PELA PLACA: INSIRA UMA PLACA PARA VERIFICAR     |\n");
            printf("\t\t|    SE O VE�CULO J� FOI CONVOCADO OU N�O PARA O PROCESSO DE TROCA DE PLACAS    |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|3 - BUSCAR SITUA��O DE VE�CULO PELO CPF DO PROPRIET�RIO: INSIRA UM CPF PARA    |\n");
            printf("\t\t|    VERIFICAR SE O VE�CULO FOI CONVOCADO OU N�O PARA A TROCA DE PLACAS         |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|4 - INSERIR PROPRIET�RIO NA BASE DE DADOS: CADASTRA UM PROPRIET�RIO N�O        |\n");
            printf("\t\t|    ENCONTRADO NA BASE DE DADOS                                                |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|6 - DESLOGAR: RETORNA PARA A TELA DE LOGIN.                                    |\n\n");
            break;
        case 6:
            printf("\nDESLOGANDO!\n\n");
            break;
        default:
            printf("\nOP��O INV�LIDA.\n\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(op != 6);
}

void * menu_admin(pessoa *sociedade)
{
    int op = 0, ret = 0, n = 0, categoria = 0;
    int i;
    char placa[9], cpf[15];

    do
    {
        system("cls");

        printf("\t\t\t\t>>>BEM VINDO AO MENU ADMINISTRADOR!<<<\n\n");
        printf("\n-> EM CASO DE D�VIDAS, ACIONE A OP��O AJUDA <-\n\n\n");
        printf("\t\t     >>> OP��ES <<<\n");
        printf("\n\t|1 - BUSCA DE CATEGORIA                                  |");
        printf("\n\t|                                                        |");
        printf("\n\t|2 - BUSCAR SITUA��O DE VE�CULO PELA PLACA               |");
        printf("\n\t|                                                        |");
        printf("\n\t|3 - BUSCAR SITUA��O DE VE�CULO PELO CPF DO PROPRIET�RIO |");
        printf("\n\t|                                                        |");
        printf("\n\t|4 - CHAMADA DE PROPRIET�RIO                             |");
        printf("\n\t|                                                        |");
        printf("\n\t|5 - RELAT�RIO DA BASE DE DADOS                          |");
        printf("\n\t|                                                        |");
        printf("\n\t|6 - ADICIONAR NOVO USU�RIO                              |");
        printf("\n\t|                                                        |");
        printf("\n\t|7 - ADMINISTRA��O DA BASE DE DADOS                      |");
        printf("\n\t|                                                        |");
        printf("\n\t|8 - AJUDA                                               |");
        printf("\n\t|                                                        |");
        printf("\n\t|9 - DESLOGAR                                            |");
        printf("\n\n\nDIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            do
            {
                system("cls");
                printf("\t\t    >>>OP��ES<<<\n");
                printf("\n\t\t|1 - DIPLOM�TICO  |");
                printf("\n\t\t|2 - APRENDIZAGEM |");
                printf("\n\t\t|3 - ALUGUEL      |");
                printf("\n\t\t|4 - PARTICULAR   |");
                printf("\n\t\t|5 - EXPERI�NCIA  |");
                printf("\n\t\t|6 - COLE��O      |\n");
                printf("\nDIGITE O N�MERO DA CATEGORIA QUE DESEJA BUSCAR: ");
                categoria = 0;
                fflush(stdin);
                scanf("%d", &categoria);

                if(categoria < 7)
                {
                    ret = busca_categoria(sociedade, categoria);//Busca a quantidade de placas que ainda faltam trocar para o padr�o MERCOSUL

                    if(ret == 0)
                    {
                        printf("\nOS VE�CULOS DA CATEGORIA INFORMADA J� TERMINARAM DE TROCAR AS PLACAS PARA O PADR�O MERCOSUL.\n\n");
                    }
                    else
                    {
                        printf("\nFALTAM %d VE�CULOS PARA TROCA DE PLACAS PARA O PADR�O MERCOSUL.\n\n", ret);
                    }
                }
                else
                {
                    printf("\nOP��O INV�LIDA!\n\n");
                    system("pause");
                }
            }
            while(categoria > 6);

            break;
        case 2:
            system("cls");
            printf("DIGITE A PLACA DO VE�CULO NO FORMATO AAA0000: ");
            placa[0] = '\0';
            fflush(stdin);
            scanf("%s", placa);

            ret = busca_veiculo(placa, sociedade);//Busca situa��o de um ve�culo espec�fica atrav�s da placa

            if(ret != 0)
            {
                printf("\nVE�CULO '%s' COM PLACA '%s' AINDA EM LISTA DE ESPERA PARA TROCA DE PLACAS.\n\n", sociedade[ret].carro, sociedade[ret].placa_carro);
            }
            else if(busca_veiculo_chamado(placa))
            {
                printf("\nVE�CULO COM PLACA %s J� INTIMADO PARA TROCA DE PLACAS.\n\n", placa);
            }
            else
            {
                printf("\nVE�CULO N�O CADASTRADO NA BASE DE DADOS\n\n");
            }
            break;
        case 3:
            system("cls");
            printf("DIGITE O CPF DO PROPRIET�RIO DO VE�CULO NO FORMATO 000.111.222-33: ");
            cpf[0] = '\0';
            fflush(stdin);
            scanf("%s", cpf);

            ret = busca_veiculo_cpf(cpf, sociedade);//Busca situa��o de um ve�culo espec�fica atrav�s do cpf

            if(ret != 0)
            {
                printf("\nVE�CULO '%s' COM PLACA '%s' AINDA EM LISTA DE ESPERA PARA TROCA DE PLACAS.\n\n", sociedade[ret].carro, sociedade[ret].placa_carro);
            }
            else if(busca_veiculo_cpf_chamado(cpf))
            {
                printf("\nPROPRIET�RIO J� INTIMADO PARA TROCA DE PLACAS.\n\n");
            }
            else
            {
                printf("\nPROPRIET�RIO N�O POSSUI NENHUM VE�CULO CADASTRADO NA BASE DE DADOS\n\n");
            }
            break;
        case 4:
            system("cls");
            n = 0;

            if(count_lines != 0)//Se ainda houverem placas para trocar, o count_lines vai ser diferente de 0
            {
                do
                {
                    printf("DIGITE A QUANTIDADE DE VE�CULOS QUE DESEJA CONVOCAR: ");
                    n = 0;
                    fflush(stdin);
                    scanf("%d", &n);
                    if(n > count_lines/5)/*e o n�mero que o usu�rio digitar for maior do que o n�mero de pessoas que faltam trocar a
                    placa, o usu�rio ter� que colocar outro n�mero que esteja dispon�vel*/
                    {
                        printf("\nN�MERO INFORMADO ULTRAPASSA O N�MERO DE PESSOAS QUE FALTAM TROCAR AS PLACAS.");
                        printf("\nFALTAM %d PESSOAS PARA TROCAR AS PLACAS.\n\n", count_lines/5);
                        system("pause");
                        system("cls");
                    }
                }
                while(n > count_lines/5);

                escrever_arq(chamada(sociedade, n));//Escreve o arquivo com a listan que ser� retornada pela fun��o chamada
                sobrescrever_arq(sociedade);//Sobrescreve o arquivo usando a struct sociedade
                free(sociedade);
                sociedade = le_arquivo();//L� o arquivo sobrescrito com os dados remanescentes
            }
            else
            {
                printf("\nTODOS OS VE�CULOS DO DF J� EST�O COM AS PLACAS DO PADR�O MERCOSUL.\n\n");
            }
            break;
        case 5:
            system("cls");
            relatorio(sociedade);//Mostra na tela um relat�rio geral da situa��o da troca de placas
            break;
        case 6:
            adicionar_login();//Adiciona novos logins a base de dados
            break;
        case 7:
            sociedade = administracao_base_dados(sociedade);//Concatena, sobrescreve e adiciona dados no arquivo inicial
            break;
        case 8://Mostra ajuda ao usu�rio
            system("cls");
            printf("\n\t\t|1 - BUSCA DE CATEGORIA: QUANTITATIVO DE VE�CULOS QUE AINDA NECESSITAM          |\n");
            printf("\t\t|    TROCAR AS PLACAS PARA O NOVO MODELO MERCOSUL                               |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|2 - BUSCAR SITUA��O DE VE�CULO PELA PLACA: INSIRA UMA PLACA PARA VERIFICAR     |\n");
            printf("\t\t|    SE O VE�CULO J� FOI CONVOCADO OU N�O PARA O PROCESSO DE TROCA DE PLACAS    |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|3 - BUSCAR SITUA��O DE VE�CULO PELO CPF DO PROPRIET�RIO: INSIRA UM CPF PARA    |\n");
            printf("\t\t|    VERIFICAR SE O VE�CULO FOI CONVOCADO OU N�O PARA A TROCA DE PLACAS         |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|4 - CHAMADA DE PROPRIET�RIO: CONVOQUE PROPRIET�RIOS PARA TROCA DE VE�CULOS     |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|5 - RELAT�RIO DA BASE DE DADOS: MOSTRA UM RELAT�RIO GERAL POR CATEGORIA:       |\n");
            printf("\t\t|    QUANTOS VE�CULOS AINDA FALTA TROCAR AS PLACAS E QUANTOS J� TROCARAM        |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|6 - ADICIONAR USU�RIO: ADICIONA NOVOS USU�RIOS A BASE DE DADOS                 |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|7 - ADMINISTRA��O DA BASE DE DADOS: ADICIONA NOVA BASE DE DADOS OU CONCATENA   |\n");
            printf("\t\t|    A BASE DE DADOS ATUAL                                                      |\n");
            printf("\t\t|                                                                               |\n");
            printf("\t\t|9 - DESLOGAR: RETORNA PARA A TELA DE LOGIN.                                    |\n\n");
            break;
        case 9://Retorna para a tela de login
            printf("\nDESLOGANDO!\n\n");
            break;
        default:
            printf("\nOP��O INV�LIDA.\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(op != 9);
}

int busca_categoria(pessoa *sociedade, int categoria)
{
    int i, ret = 0;

    for(i=0; i<num_dados; i++)
    {
        if(categoria == sociedade[i].prioridade)
        {
            ret++;
        }
    }

    return ret;
}

lista * chamada(pessoa *sociedade, int n)
{
    lista *novo_arq = NULL;
    no *aux, *novo;
    int op = 0;
    int i;

    novo_arq = aloca_lista();

    for(i=0; i<n; i++)
    {
        novo = aloca_no(remover(sociedade));//Remove de um por um da fila de prioridades e coloca em um novo n� para inserir na lista

        if(novo_arq->inicio == NULL)//Insere na lista o n� ve�culo removido
        {
            novo_arq->inicio = novo;
        }
        else
        {
            aux = novo_arq->inicio;
            while(aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
        novo_arq->qtd++;
    }

    do
    {
        printf("\nGOSTARIA DE VISUALIZAR OS VE�CULOS CONVOCADOS? DIGITE 1 PARA VISUALIZAR OU 2 PARA SAIR: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            mostrar_convocados(novo_arq->inicio);//Mostra todos os ve�culos que foram chamados para trocar as placas
            op = 2;
            break;
        case 2:
            printf("\nSUCESSO! FORAM CONVOCADOS %d VE�CULOS!\n\n", n);
            break;
        default:
            printf("\nOP��O INV�LIDA!");
        }
    }
    while(op != 2);

    return novo_arq;
}

pessoa remover(pessoa *sociedade)
{
    int filho1 = 0, filho2 = 0, pai = 0;
    pessoa aux;

    aux = sociedade[1];

    pai = 1;
    filho1 = pai * 2;
    filho2 = pai * 2 + 1;

    do
    {
        if(sociedade[filho1].prioridade > sociedade[filho2].prioridade)/*Verifica qual dos dois filhos tem maior prioridade
        e o coloca na posi��o do pai*/
        {
            sociedade[pai] = sociedade[filho1];
            pai = filho1;
        }
        else
        {
            sociedade[pai] = sociedade[filho2];
            pai = filho2;
        }
        filho1 = pai * 2;//Recalcula os filhos e faz o la�o enquanto o filho1 for menor que o tamanho de pessoas que ainda h� na base
        filho2 = pai * 2 + 1;
    }
    while(filho1 <= num_dados);

    limpar_folha(&sociedade[pai]);//Limpa a �ltima posi��o que sobrou na �rvore

    return aux;
}

void limpar_folha(pessoa *sociedade)
{
    strcpy(sociedade->nome, "");
    strcpy(sociedade->cpf, "");
    strcpy(sociedade->carro, "");
    strcpy(sociedade->categoria_carro, "");
    strcpy(sociedade->placa_carro, "");
    sociedade->prioridade = 0;
}

void mostrar_convocados(no *aux)
{
    while(aux != NULL)//Enquanto o aux != NULL, mostra os dados das pessoas chamadas para troca de placas
    {
        printf("\n\t|%s|\n", aux->carro);
        printf("\t|%s|\n\n", aux->placa_carro);
        aux = aux->prox;
    }
}

int busca_veiculo(char *placa, pessoa *sociedade)
{
    int i;

    for(i=0; i<num_dados; i++)
    {
        if(stricmp(placa, sociedade[i].placa_carro) == 0)
        {
            return i;
        }
    }

    return 0;
}

int busca_veiculo_chamado(char *placa)
{
    FILE *arq;
    char a[50];

    arq = fopen("mercosul.txt", "r");//Verifica se a placa j� foi cadastrada no arquivo de chamados

    if(arq != NULL)
    {
        if(placa[4] == '0')
        {
            placa[4] = 'A';
        }
        if(placa[4] == '1')
        {
            placa[4] = 'B';
        }
        if(placa[4] == '2')
        {
            placa[4] = 'C';
        }
        if(placa[4] == '3')
        {
            placa[4] = 'D';
        }
        if(placa[4] == '4')
        {
            placa[4] = 'E';
        }
        if(placa[4] == '5')
        {
            placa[4] = 'F';
        }
        if(placa[4] == '6')
        {
            placa[4] = 'G';
        }
        if(placa[4] == '7')
        {
            placa[4] = 'H';
        }
        if(placa[4] == '8')
        {
            placa[4] = 'I';
        }
        if(placa[4] == '9')
        {
            placa[4] = 'J';
        }

        while(!feof(arq))
        {
            fgets(a, 50, arq);
            a[strcspn(a, "\n")] = 0;

            if(stricmp(a, placa) == 0)
            {
                fclose(arq);
                return 1;
            }
        }
    }

    return 0;
}

int busca_veiculo_cpf(char *cpf, pessoa * sociedade)
{
    int i;

    for(i=0; i<num_dados; i++)
    {
        if(stricmp(cpf, sociedade[i].cpf) == 0)
        {
            return i;
        }
    }

    return 0;
}

int busca_veiculo_cpf_chamado(char *cpf)
{
    FILE *arq;
    char a[50];

    arq = fopen("mercosul.txt", "r");//Verifica se o CPF est� no arquivo de chamados

    if(arq != NULL)
    {
        while(!feof(arq))
        {
            fgets(a, 50, arq);
            a[strcspn(a, "\n")] = 0;

            if(stricmp(a, cpf) == 0)
            {
                fclose(arq);
                return 1;
            }
        }
    }

    return 0;
}

void relatorio(pessoa *sociedade)
{
    int i;
    int priority = 0;
    int k = 0;
    int t1 = 0, t2 = 0, t3 = 0;
    int rel[12];
    char a[50];
    FILE *arq;

    for(i=0; i<12; i++)//Inicializa todas as posi��es com 0
    {
        rel[i] = 0;
    }

    for(i=0; i<6; i++)//Faz a contagem dos ve�culos que faltam trocar as placas usando a fun��o busca categoria
    {
        rel[i] = busca_categoria(sociedade, i+1);
    }

    arq = fopen("mercosul.txt", "r");//Faz a pesquisa dos ve�culos que trocaram lendo o arquivo mercosul

    if(arq != NULL)
    {
        while(!feof(arq))
        {
            fgets(a, 50, arq);
            a[strcspn(a, "\n")] = 0;

            if(stricmp(a, "Diplomatico") == 0)
            {
                rel[6]++;
            }
            else if(stricmp(a, "Especial") == 0)
            {
                if(rel[10] <= 83601)
                {
                    rel[10]++;
                }
                else
                {
                    rel[7]++;
                }
            }
            else if(stricmp(a, "Comercial") == 0)
            {
                rel[8]++;
            }
            else if(stricmp(a, "Particular") == 0)
            {
                rel[9]++;
            }
            else if(stricmp(a, "Colecionador") == 0)
            {
                rel[11]++;
            }
        }
        fclose(arq);
    }

    t1 = rel[0] + rel[1] + rel[2] + rel[3] + rel[4] + rel[5];
    t2 = rel[6] + rel[7] + rel[8] + rel[9] + rel[10] + rel[11];
    t3 = t1 + t2;

    printf("\n\t|Categorias   |   Faltam trocar   |    Trocas Realizadas   |   Total   |\n");
    printf("\t|Aluguel      |       %.6d      |         %.6d         |   %.6d  |\n", rel[2], rel[8], rel[2] + rel[8]);
    printf("\t|Cole��o      |       %.6d      |         %.6d         |   %.6d  |\n", rel[5], rel[11], rel[5] + rel[11]);
    printf("\t|Particular   |       %.6d      |         %.6d         |   %.6d  |\n", rel[3], rel[9], rel[3] + rel[9]);
    printf("\t|Diplom�tico  |       %.6d      |         %.6d         |   %.6d  |\n", rel[0], rel[6], rel[0] + rel[6]);
    printf("\t|Experi�ncia  |       %.6d      |         %.6d         |   %.6d  |\n", rel[4], rel[10], rel[4] + rel[10]);
    printf("\t|Aprendizagem |       %.6d      |         %.6d         |   %.6d  |\n", rel[1], rel[7], rel[1] + rel[7]);
    printf("\t|-------------|-------------------|------------------------|-----------|\n");
    printf("\t|Total        |       %.6d      |         %.6d         |   %.6d  |\n\n", t1, t2, t3);

    if(count_lines != 0)
    {
        printf("\t\t\tPR�XIMOS VE�CULOS PARA TROCA DE PLACAS: \n\n");

        priority = sociedade[1].prioridade;

        i = 1;

        do//Mostra os pr�ximos 10 ve�culos na fila de prioridade
        {
            printf("\t| VE�CULO   : %s  |\n", sociedade[i].carro);
            printf("\t| PLACA     : %s  |\n", sociedade[i].placa_carro);
            printf("\t| CATEGORIA : %s  |\n\n", sociedade[i].categoria_carro);

            k++;
            i++;
            while(sociedade[i].prioridade != priority)
            {
                i++;
            }
        }
        while(k <= 10);
    }
}

void adicionar_login()
{
    FILE *arq;
    int op = 0;
    char login[50];
    char senha[7];
    char a[50];
    int i;

    do
    {
        system("cls");
        printf("\t\t\t >>> OP��ES <<<\n\n");
        printf("\t\t|1 - INSERIR LOGIN DE AGENTE         |\n");
        printf("\t\t|                                    |\n");
        printf("\t\t|2 - INSERIR LOGIN DE ADMINISTRADOR  |\n");
        printf("\t\t|                                    |\n");
        printf("\t\t|3 - VOLTAR AO MENU PRINCIPAL        |\n");
        printf("\nDIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("\nDIGITE O LOGIN (OBS.: DEVE CONTER ATE 50 CARACTERES): ");
            fflush(stdin);
            gets(login);
            printf("\nDIGITE A SENHA (OBS.: DEVE CONTER ATE 6 CARACTERES): ");
            fflush(stdin);
            gets(senha);

            arq = fopen("login_agente.txt", "a+");

            while(!feof(arq))//Verifica se o login j� est� cadastrado na base de dados. Se estiver, n�o insere nada no arquivo
            {
                fflush(stdin);
                fgets(a, 50, arq);
                a[strcspn(a, "\n")] = 0;
                if(stricmp(login, a) == 0)
                {
                    printf("\nLOGIN J� CADASTRADO.\n");
                    fclose(arq);
                    system("pause");
                    break;
                }
            }

            fprintf(arq, "%s\n%s\n", login, senha);//Insere o login na base de dados

            fclose(arq);
            break;
        case 2:

            printf("\nDIGITE O LOGIN (OBS.: DEVE CONTER ATE 50 CARACTERES): ");
            fflush(stdin);
            gets(login);
            printf("\nDIGITE A SENHA (OBS.: DEVE CONTER ATE 6 CARACTERES): ");
            fflush(stdin);
            gets(senha);

            arq = fopen("login_admin.txt", "a+");

            while(!feof(arq))//Verifica se o login j� est� cadastrado na base de dados. Se estiver, n�o insere nada no arquivo
            {
                fflush(stdin);
                fgets(a, 50, arq);
                a[strcspn(a, "\n")] = 0;
                if(stricmp(login, a) == 0)
                {
                    printf("\nLOGIN J� CADASTRADO.\n");//Insere o login na base de dados
                    fclose(arq);
                    break;
                }
            }

            fprintf(arq, "%s\n%s\n", login, senha);

            fclose(arq);
            break;
        case 3://Volta para o menu admin
            break;
        default:
            printf("\nOP��O INV�LIDA!\n");
            break;
        }
    }
    while(op != 3);
}

pessoa * administracao_base_dados(pessoa * sociedade)
{
    int i;
    int op = 0, teste = 0;
    char nome_arq[50], command[200], aux[10], a[50];
    FILE *arq, *arq2;
    pessoa novo;

    do
    {
        fflush(stdin);
        system("cls");
        printf("\t\t\t\t     >>> OP��ES <<<\n\n");
        printf("\t\t|1 - ADICIONAR UMA BASE DE DADOS A BASE EXISTENTE            |\n");
        printf("\t\t|                                                            |\n");
        printf("\t\t|2 - SOBRESCREVER A BASE DE DADOS EXISTENTE COM UMA NOVA BASE|\n");
        printf("\t\t|                                                            |\n");
        printf("\t\t|3 - ADICIONAR PROPRIET�RIO A BASE DE DADOS                  |\n");
        printf("\t\t|                                                            |\n");
        printf("\t\t|4 - SAIR                                                    |\n\n");
        printf("Digite a op��o desejada: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        system("cls");

        switch(op)
        {
        case 1:
            printf("\t\t\t   >>> REQUISITOS B�SICOS DO ARQUIVO <<<\n\n");//Explica os requisitos b�sicos de arquivo pra ser inserido
            printf(" |1 - EXTENS�O DO ARQUIVO: .txt                                                                    |\n");
            printf(" |                                                                                                 |\n");
            printf(" |2 - O NOME DO ARQUIVO TEM QUE ESTAR DIGITADO SEM ESPA�OS                                         |\n");
            printf(" |                                                                                                 |\n");
            printf(" |3 - O ARQUIVO DEVER� ESTAR NA MESMA PASTA QUE ARQUIVO DEVER� ESTAR NA MESMA PASTA QUE O PROGRAMA |\n");
            printf(" |                                                                                                 |\n");
            printf(" |4 - EXEMPLO DE FORMATA��O DO ARQUIVO:                                                            |\n");
            printf(" |                                                                                                 |\n");
            printf(" |NOME DO PROPRIET�RIO:                                                                            |\n");
            printf(" |CPF DO PROPRIET�RIO (000.111.222-33)                                                             |\n");
            printf(" |MARCA/MODELO DO VE�CULO                                                                          |\n");
            printf(" |CATEGORIA DO VE�CULO POR EXTENSO                                                                 |\n");
            printf(" |PLACA DO VE�CULO(AAA0000)                                                                        |\n");
            printf(" |                                                                                                 |\n");
            printf(" |5 - CATEGORIAS DE VE�CULOS V�LIDAS:                                                              |\n");
            printf(" |    PARTICULAR, ALUGUEL, DIPLOMATICO, EXPERIENCIA, COLECAO, APRENDIZAGEM.                        |\n");
            printf(" |                                                                                                 |\n");
            printf(" |6 - TODAS AS CATEGORIAS DEVEM SER ESCRITAS SEM ACENTOS OU CARACTERES ESPECIAIS COMO �.           |\n\n");
            printf("DIGITE O NOME DO ARQUIVO: ");

            fflush(stdin);
            scanf("%s", nome_arq);

            command[0] = '\0';//Come�am a fazer uma linha de comando para o system concatenar os arquivos
            strcat(nome_arq, ".txt");
            strcat(command, "type ");
            strcat(command, nome_arq);
            strcat(command, " >> eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt");
            //linha de comando ficar� assim: "type arq_origem.txt >> arq_destino.txt "
            //Como tudo estar� em uma vari�vel, n�o � necess�rio colocar aspas

            if(!system(command))//Se der certo a concatena��o dos arquivos: l� o novo arquivo e mostra que deu certo a fun��o
            {
                free(sociedade);
                sociedade = le_arquivo();
                printf("\nJUN��O DE ARQUIVOS FEITA COM SUCESSO!\n\n");
            }
            else//Se n�o der certo, avisa o que pode estar errado.
            {
                printf("VERIFIQUE SE O ARQUIVO EST� NA MESMA PASTA QUE O PROGRAMA E SE O NOME DO ARQUIVO EST� CORRETO.\n\n");
            }

            system("pause");

            break;

        case 2:
            printf("\t\t\t   >>> REQUISITOS B�SICOS DO ARQUIVO <<<\n\n");//Explica os requisitos b�sicos de arquivo pra ser inserido
            printf(" |1 - EXTENS�O DO ARQUIVO: .txt                                                                    |\n");
            printf(" |                                                                                                 |\n");
            printf(" |2 - O NOME DO ARQUIVO TEM QUE ESTAR DIGITADO SEM ESPA�OS                                         |\n");
            printf(" |                                                                                                 |\n");
            printf(" |3 - O ARQUIVO DEVER� ESTAR NA MESMA PASTA QUE ARQUIVO DEVER� ESTAR NA MESMA PASTA QUE O PROGRAMA |\n");
            printf(" |                                                                                                 |\n");
            printf(" |4 - EXEMPLO DE FORMATA��O DO ARQUIVO:                                                            |\n");
            printf(" |                                                                                                 |\n");
            printf(" |NOME DO PROPRIET�RIO:                                                                            |\n");
            printf(" |CPF DO PROPRIET�RIO (000.111.222-33)                                                             |\n");
            printf(" |MARCA/MODELO DO VE�CULO                                                                          |\n");
            printf(" |CATEGORIA DO VE�CULO POR EXTENSO                                                                 |\n");
            printf(" |PLACA DO VE�CULO(AAA0000)                                                                        |\n");
            printf(" |                                                                                                 |\n");
            printf(" |5 - CATEGORIAS DE VE�CULOS V�LIDAS:                                                              |\n");
            printf(" |    PARTICULAR, ALUGUEL, DIPLOMATICO, EXPERIENCIA, COLECAO, APRENDIZAGEM.                        |\n");
            printf(" |                                                                                                 |\n");
            printf(" |6 - TODAS AS CATEGORIAS DEVEM SER ESCRITAS SEM ACENTOS OU CARACTERES ESPECIAIS COMO �.           |\n\n");
            printf("DIGITE O NOME DO ARQUIVO: ");

            fflush(stdin);
            scanf("%s", nome_arq);

            command[0] = '\0';//Come�am a fazer uma linha de comando para o system sobrescrever o arquivo inicial
            strcat(nome_arq, ".txt");
            strcat(command, "type ");
            strcat(command, nome_arq);
            strcat(command, " > eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt");
            //linha de comando ficar� assim: "type arq_origem.txt > arq_destino.txt "
            //Como tudo estar� em uma vari�vel, n�o � necess�rio colocar aspas

            if(!system(command))//Se der certo sobrescrever o arquivo: l� o novo arquivo e mostra que deu certo a fun��o
            {
                free(sociedade);
                sociedade = le_arquivo();
                printf("\nARQUIVO SOBRESCRITO COM SUCESSO!\n\n");
            }
            else//Se n�o der certo, avisa o que pode estar errado.
            {
                printf("VERIFIQUE SE O ARQUIVO EST� NA MESMA PASTA QUE O PROGRAMA E SE O NOME DO ARQUIVO EST� CORRETO.\n\n");
            }

            system("pause");

            break;

        case 3:
            inserir_proprietario(sociedade);
            free(sociedade);
            sociedade = le_arquivo();

            system("pause");

            break;

        case 4://Retorna ao menu_admin
            break;

        default:
            printf("\nOP��O INV�LIDA\n\n");
            system("pause");
            break;
        }
    }
    while(op != 4);

    return sociedade;
}

void inserir_proprietario(pessoa *sociedade)
{
    pessoa novo;
    int teste = 0;
    int op = 0;
    int i;
    char a[50];
    char aux[15];
    FILE *arq;

    do
    {
        system("cls");

        printf("\t\t\t>>> OP��ES <<<\n\n");
        printf("\t|1 - INSERIR NOVO PROPRIET�RIO |\n");
        printf("\t|2 - VOLTAR AO MENU PRINCIPAL  |\n");
        printf("\n\nDIGITE A OP��O DESEJADA: ");
        op = 0;
        fflush(stdin);
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("\nDIGITE O NOME DO PROPRIET�RIO: ");//L� do usu�rio os dados da nova pessoa
            fflush(stdin);
            fgets(novo.nome, 50, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = 0;
            printf("\nDIGITE O CPF DO PROPRIET�RIO NA FORMATA��O 000.111.222-33: ");
            fflush(stdin);
            fgets(novo.cpf, 15, stdin);
            novo.cpf[strcspn(novo.cpf, "\n")] = 0;
            printf("\nDIGITE A MARCA/MODELO DO VE�CULO: ");
            fflush(stdin);
            fgets(novo.carro, 50, stdin);
            novo.carro[strcspn(novo.carro, "\n")] = 0;
            printf("\nDIGITE A CATEGORIA DO VE�CULO: ");
            fflush(stdin);
            fgets(novo.categoria_carro, 15, stdin);
            novo.categoria_carro[strcspn(novo.categoria_carro, "\n")] = 0;
            printf("\nDIGITE A PLACA DO VE�CULO NA FORMATA��O ABC0123: ");
            fflush(stdin);
            fgets(novo.placa_carro, 10, stdin);
            novo.placa_carro[strcspn(novo.placa_carro, "\n")] = 0;

            free(sociedade);
            sociedade = le_arquivo();

            for(i=1; i<num_dados; i++)/*Verifica pela placa se o carro j� foi cadastrado e se a resposta for sim,
            ele da um break no case*/
            {
                if(stricmp(novo.placa_carro, sociedade[i].placa_carro) == 0)
                {
                    printf("\nPLACA DO CARRO INFORMADO J� EST� NA BASE DE DADOS.\n\n");
                    teste = 1;
                    break;
                }
            }

            arq = fopen("mercosul.txt", "r");//Verifica pela placa se o carro j� foi cadastrado lendo o arquivo mercosul

            if(arq != NULL)
            {
                strcpy(aux, novo.placa_carro);
                if(aux[4] == '0')
                {
                    aux[4] = 'A';
                }
                if(aux[4] == '1')
                {
                    aux[4] = 'B';
                }
                if(aux[4] == '2')
                {
                    aux[4] = 'C';
                }
                if(aux[4] == '3')
                {
                    aux[4] = 'D';
                }
                if(aux[4] == '4')
                {
                    aux[4] = 'E';
                }
                if(aux[4] == '5')
                {
                    aux[4] = 'F';
                }
                if(aux[4] == '6')
                {
                    aux[4] = 'G';
                }
                if(aux[4] == '7')
                {
                    aux[4] = 'H';
                }
                if(aux[4] == '8')
                {
                    aux[4] = 'I';
                }
                if(aux[4] == '9')
                {
                    aux[4] = 'J';
                }
                while(!feof(arq))
                {
                    fgets(a, 50, arq);
                    a[strcspn(a, "\n")] = 0;

                    if(stricmp(a, aux) == 0)
                    {
                        printf("\nPLACA DO CARRO INFORMADO J� EST� NA BASE DE DADOS.\n\n");
                        teste = 1;
                        fclose(arq);
                        break;
                    }
                }
            }

            if(teste == 1)//se teste ficar com o valor igual a 1 � porque a placa que o usu�rio deseja inserir j� est� cadastrado
            {
                break;
            }
            else//Sen�o, insere o novo propriet�rio ao arquivo e rel� o arquivo
            {
                arq = fopen("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt", "a");
                fprintf(arq, "%s\n%s\n%s\n%s\n%s\n", novo.nome, novo.cpf, novo.carro, novo.categoria_carro, novo.placa_carro);
                fclose(arq);
                printf("\nPROPRIET�RIO INSERIDO COM SUCESSO!\n\n");
            }
            break;
        case 2:
            printf("\nRETORNANDO AO MENU!\n\n");
            break;
        default:
            printf("\nOP��O INV�LIDA\n");
            break;
        }

        system("pause");
    }
    while(op != 2);
}

void escrever_arq(lista *a)
{
    no *aux;
    FILE *arq;

    //Coloca no arquivo as pessoas chamadas para troca de placas

    arq = fopen("mercosul.txt", "a");

    if(arq == NULL)
    {
        printf("ERRO NA ABERTURA DO ARQUIVO.\n");
    }

    aux = a->inicio;

    while(aux != NULL)
    {
        fprintf(arq, "%s\n%s\n%s\n%s\n%s\n", aux->nome, aux->cpf, aux->carro, aux->categoria_carro, aux->placa_carro);
        aux = aux->prox;
    }

    fclose(arq);
}

void sobrescrever_arq(pessoa *sociedade)
{
    int i;
    FILE *arq;

    //Sobrescreve o arquivo inicial com os dados das pessoas remanescentes para troca de placas

    arq = fopen("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.txt", "w");

    for(i=1; i<num_dados; i++)
    {
        if(sociedade[i].prioridade != 0)
        {
            fprintf(arq, "%s\n%s\n%s\n%s\n%s\n", sociedade[i].nome, sociedade[i].cpf, sociedade[i].carro, sociedade[i].categoria_carro, sociedade[i].placa_carro);
        }
    }

    fclose(arq);
}
