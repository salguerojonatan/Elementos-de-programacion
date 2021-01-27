#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Declaracion de estructuras */
typedef struct{
    int codigo;
    char descripcion[35];
    int stock;
    float precio;
}t_producto;

typedef struct{
    int codigo;
    int cantVendidas;
    int cliente;
    int dia;
    char estado[11];
}t_pedido;

typedef struct{
    int dia;
    int cantidad;
    float total;
}t_monto;

/* <- FIN -> */
/* Declaracion de prototipos de funciones */
int mostrarListado();
int cargaProducto(int);
void cargaPedido();
void listarContenido();
int validarDato(int, int, int);
int buscar(t_producto [],int, t_pedido);
void mostrarPedidos();
void mostrarProductos();
void informeCantidadYMontos();
int cantidadProductos();
void ordenar(t_monto [], int);
void informePedidosNoStock();
/* <- FIN FUNCIONES -> */

int main()
{
    int cantProductos = 0;
    int opc;

    do{
        opc=mostrarListado();
    }while(validarDato(opc, 1, 6) == 0);

    while(opc != 6){

        switch(opc){
        case 1:
            cantProductos =cargaProducto(100);
            break;
        case 2:
            cantProductos =cantidadProductos();
            cargaPedido(cantProductos);
            break;
        case 3:
            listarContenido();
            break;
        case 4:
            informeCantidadYMontos();
            break;
        case 5:
            informePedidosNoStock();
            break;
        }

    do{
        opc=mostrarListado();
    }while(validarDato(opc, 1, 6) == 0);

    }



    return 0;
}

/* FUNCIONES */

int validarDato(int dato, int li , int ls){
    if( dato < li || dato > ls)
        return 0;
    return 1;
}

int mostrarListado(){
    int opc;
    do{
    printf("\t1 - Carga de productos.\n");
    printf("\t2 - Carga de pedidos.\n");
    printf("\t3 - Listar contenidos de archivos.\n");
    printf("\t4 - Informar cantidad y montos vendidos.\n");
    printf("\t5 - Mostrar Archivo pedidos no complidos por falta de stock.\n");
    printf("\t6 - Salir.\n");
    printf("Elegir opcion: ");
    scanf("%d", &opc);
    }while(opc < 1 || opc > 6);

    return opc;
}

void cargaPedido(int cantProductos){

    FILE *fpProductos, *fpPedidos,*fpProNStock;

    t_producto vectProducto[cantProductos];
    int i = 0;
    t_producto info;
    t_pedido pedido;
    int pos;

    // BAJADA DE ARCHIVO productos.dat A VECTOR
    fpProductos = fopen("productos.dat", "rb");
    if(fpProductos == NULL || cantProductos == 0){
        printf("NO SE INGRESARON PRODUCTOS");
        exit(0);
    }

    fread(&info, sizeof(t_producto),1 ,fpProductos);
    while(!feof(fpProductos)){
        vectProducto[i] = info;
        i++;
        fread(&info, sizeof(t_producto),1 ,fpProductos);
    }
    fclose(fpProductos);
   // <- FIN ->

        fpPedidos = fopen("pedidos.dat", "wb");
        fpProNStock = fopen("Pedi_No.dat", "wb");

        if(fpPedidos == NULL || fpProNStock == NULL){
            exit(0);
        }
    // INGRESO DE PEDIDOS

    do{
        printf("Ingrese codigo de pedido: ");
        scanf("%d", &pedido.codigo);
    }while(validarDato(pedido.codigo, 1000, 10000) == 0 && pedido.codigo != 0);


    while(pedido.codigo != 0){
        pos = buscar(vectProducto, cantProductos, pedido);
        if(pos != -1){
            do{
                printf("Ingrese la cantidad vendida: ");
                scanf("%d", &pedido.cantVendidas);
            }while(pedido.cantVendidas < 1);

            do{
                printf("Ingrese numero de cliente: ");
                scanf("%d", &pedido.cliente);
            }while(validarDato(pedido.cliente, 1, 350)==0);

            do{
                printf("Ingrese dia de venta (1 a 30): ");
                scanf("%d", &pedido.dia);
            }while(validarDato(pedido.dia,1,30) == 0);

            if(pedido.cantVendidas < vectProducto[pos].stock){
                vectProducto[pos].stock-=pedido.cantVendidas;
                strcpy(pedido.estado, "DESCONTADO");
                fwrite(&pedido, sizeof(t_pedido),1,fpPedidos);
            }
            else{
                strcpy(pedido.estado, "PENDIENTE");
                fwrite(&pedido, sizeof(t_pedido),1,fpProNStock);
            }


        }
        else{
            printf("PRODUCTO INEXISTENTE\n");
        }

        do{
            printf("Ingrese codigo de pedido: ");
            scanf("%d", &pedido.codigo);
        }while(validarDato(pedido.codigo, 1000, 10000) == 0 && pedido.codigo != 0);
    }
    fclose(fpPedidos);
    fclose(fpProNStock);
      // <- FIN ->

      //ACTUALIZAMOS PRODUCTOS.DAT

      fpProductos = fopen("productos.dat", "wb");
      if(fpProductos == NULL)
      {
          printf("ERROR AL LEER ARCHIVO");
          exit(0);
      }

      for(i = 0; i<cantProductos; i++)
        fwrite(&vectProducto[i], sizeof(t_producto),1,fpProductos);
    fclose(fpProductos);

}
void listarContenido(){
    int op;

    do{
        printf("Que archivo desea ver?\n");
        printf("1 - Productos\n");
        printf("2 - Pedidos\n");
        printf("Elija opcion: ");
        scanf("%d", &op);
    }while(validarDato(op, 1, 2) == 0);

    switch (op){
    case 1:
        mostrarProductos();
        break;
    case 2:
        mostrarPedidos();
        break;
     default:
        break;}
}

void mostrarPedidos(){
    FILE *fp;
    t_pedido info;
    fp=fopen("pedidos.dat", "rb");
    if(fp == NULL){
        printf("Error al abrir archivo");
        exit(0);
    }
    printf("CODIGO\tCANTIDAD SOLICITADA\tNUMERO DE CLIENTE\tDIA\tESTADO\n");
    fread(&info, sizeof(t_pedido),1, fp);
    while(!feof(fp)){
    printf("%d\t\t%d\t\t\t%d\t\t%d\t%s\n", info.codigo, info.cantVendidas, info.cliente, info.dia, info.estado);
    fread(&info, sizeof(t_pedido),1, fp);
    }
    fclose(fp);
    getch();
    system("cls");
}


void mostrarProductos(){
    FILE *fp;
    t_producto info;
    fp=fopen("productos.dat", "rb");
    if(fp == NULL){
        printf("Error al abrir archivo");
        exit(0);
    }
    printf("CODIGO\tDESCRIPCION\tSTOCK\tPRECIO\n");
    fread(&info, sizeof(t_producto),1, fp);
    while(!feof(fp)){
    printf("%d\t%s\t%d\t%f\n", info.codigo, info.descripcion, info.stock, info.precio);
    fread(&info, sizeof(t_producto),1, fp);
    }
    fclose(fp);
    getch();
    system("cls");
}

int buscar(t_producto vec[], int cant, t_pedido dato){
    int i=0;

    while(i<cant){
        if(dato.codigo == vec[i].codigo)
            return i;
        i++;
    }

    return -1;
}
int cargaProducto(int n){

    int arch;
    int cantidad = 0;
    t_producto info;
    FILE *fp;

    do{
        printf("\t1 - NUEVO ARCHIVO\n");
        printf("\t2 - CARGAR NUEVOS DATOS SIN BORRAR NINGUN REGISTRO\n");
        printf("Elegir opcion: ");
        scanf("%d", &arch);
    }while(validarDato(arch, 1,2) == 0);

    if(arch == 1)
        fp = fopen("productos.dat", "wb");
    else{
        cantidad = cantidadProductos();
        fp = fopen("productos.dat", "ab");
    }

    if(fp == NULL){
        printf(" ERROR EN ARCHIVO productos.dat\n");
        return 0;
    }


    /* INGRESO DE PRODUCTO */
    do{
    printf("Ingrese codigo de producto (entre 1000 y 10000): ");
    scanf("%d", &info.codigo);
    }while(validarDato(info.codigo, 1000, 10000) == 0 && info.codigo != 0);

    while(info.codigo != 0 && cantidad <= n){
        printf("Ingrese una descripcion: ");
        fflush(stdin);
        gets(info.descripcion);

        do{
            printf("Ingrese el stock (>0): ");
            scanf("%d", &info.stock);
        }while(info.stock < 1);

        do{
            printf("Ingrese el precio por unidad (>0): ");
            scanf("%f", &info.precio);
        }while(info.precio < 1);

        fwrite(&info, sizeof(t_producto),1 , fp);
        cantidad++;

        do{
            printf("Ingrese codigo de producto (entre 1000 y 10000): ");
            scanf("%d", &info.codigo);
        }while(validarDato(info.codigo, 1000, 10000) == 0 && info.codigo != 0);

    }
    /* <- FIN -> */
        fclose(fp);
        return cantidad;
}

int cantidadProductos(){
    int canti = 0;
    FILE *fp;
    t_producto info;

    fp = fopen("productos.dat", "rb");
    if(fp == NULL){
        printf("ERROR EN ARCHIVO");
        return 0;
    }

    fread(&info, sizeof(t_producto),1 , fp);

    while(!feof(fp)){
        canti++;
        fread(&info, sizeof(t_producto),1 , fp);
    }
    fclose(fp);

    return canti;
}

void informeCantidadYMontos(){
    t_monto vec[30];
    int cantProduc = cantidadProductos();
    t_pedido info;
    t_producto vecP[cantProduc];
    t_producto prod;
    int busq;
    int i,j;
    FILE *fp, *fpProd;

    fp=fopen("pedidos.dat", "rb");
    fpProd = fopen("productos.dat", "rb");

    if(fp == NULL || fpProd == NULL){
        printf("ERROR AL LEER ARCHIVO.");
        exit(0);
    }

    for(i=0;i<30;i++){
        vec[i].cantidad=0;
        vec[i].dia = i+1;
        vec[i].total = 0;
    }
    j=0;
    fread(&prod, sizeof(t_producto),1,fpProd);
    while(!feof(fpProd)){
        vecP[j] = prod;
        j++;
        fread(&prod, sizeof(t_producto),1,fpProd);
    }

    fread(&info, sizeof(t_pedido),1,fp);
    while(!feof(fp)){
        busq = buscar(vecP, cantProduc, info);
        if(busq != -1){
            vec[info.dia-1].cantidad +=info.cantVendidas;
            vec[info.dia-1].total+=info.cantVendidas * vecP[busq].precio;
        }
        fread(&info, sizeof(t_pedido),1,fp);
    }
    fclose(fp);
    fclose(fpProd);
    ordenar(vec, 30);

    printf("\tDIA\tCantidad de productos\t\tMonto Ventas\n");
    for(i=0;i<30;i++){
        if(vec[i].total>0)
            printf("\t%d\t\t%d\t%.2f\n", vec[i].dia,vec[i].cantidad, vec[i].total);
    }
    getch();
    system("cls");
}

void ordenar(t_monto vec[], int cant){
    int i,j;
    t_monto aux;
    for(i=0;i<cant-1;i++)
        for(j=0;j<cant-1-i;j++)
            if(vec[j].total<vec[j+1].total)
            {
                aux=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=aux;
            }

}

void informePedidosNoStock(){
    FILE *fpProductos, *fpProNStock;
    int cantProductos = cantidadProductos();
    t_producto vectProducto[cantProductos];
    int i = 0;
    t_producto info;
    t_pedido pedido;
    int pos;
    int cont=0;


    // BAJADA DE ARCHIVO productos.dat A VECTOR
    fpProductos = fopen("productos.dat", "rb");
    if(fpProductos == NULL || cantProductos == 0){
        printf("NO SE INGRESARON PRODUCTOS");
        exit(0);
    }

    fread(&info, sizeof(t_producto),1 ,fpProductos);
    while(!feof(fpProductos)){
        vectProducto[i] = info;
        i++;
        fread(&info, sizeof(t_producto),1 ,fpProductos);
    }
    fclose(fpProductos);
    // <- FIN ->

    fpProNStock = fopen("Pedi_No.dat", "rb");
    if(fpProNStock == NULL){
        printf("ERROR AL LEER ARCHIVO\n");
        exit(0);
    }
    printf("Codigo\tDescripcion\tStock\tCant-Pedida\tCliente\tEstado\n");
    fread(&pedido, sizeof(t_pedido),1, fpProNStock);
    while(!feof(fpProNStock)){
        pos=buscar(vectProducto, cantProductos, pedido);
        if(pos != -1){
            printf("%d\t%s\t%d\t%d\t%d\%s\n", pedido.codigo, vectProducto[pos].descripcion, vectProducto[pos].stock, pedido.cantVendidas, pedido.cliente, pedido.estado);
        }

        cont++;
       fread(&pedido, sizeof(t_pedido),1, fpProNStock);
    }

    if(cont == 0){
        system("cls");
        printf("SE CUMPLIERON TODOS LOS PEDIDOS");
    }


    getch();
    system("cls");
}
