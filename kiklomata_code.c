#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "csparse.h"
struct antikimeno
{
    char onoma[100];
    char ypsilo_dinam[100];
    char xamilo_dinam[100];
    float timi;
} antikimeno;

typedef struct pinakas_komvon
{
    char onoma[100];

} pinakas_komvon;


int metritis_grammon(FILE *file);
void menu(int choice);
void emfanisi_kiklomatikon_stoixion(struct antikimeno *s1,int size);
void topothetisi_sthn_lista(FILE *file, struct antikimeno *s1,int size);
int pinakas_komvon_sinartisi(struct antikimeno *s1,struct pinakas_komvon *s2,int size, int size2);
void ektiposi_kiklomatos(struct antikimeno *s1,int size);
void methodos_sosti(FILE *file, int size,struct pinakas_komvon *s2, int size2,struct antikimeno *s1,int epilogi);
void methodos_LxU(float **arrayA,float *arrayB,int size2);
void methodos_gacobi_gauss_sieder(float **arrayA,float *arrayB,int size2);
void methodos_araion_pinakon(FILE *file, float *arrayB,struct pinakas_komvon *s2,int size2,int size);

int main(int argc, char *argv[]) {
    FILE *file;
    struct antikimeno *s1;
    struct pinakas_komvon *s2;
    int size = 1,i=0,j=0,size2=1,found=0,epilogi=-1;
    
    char comparisonChar = 'V';
    

    if (argc != 2) {
        printf("xrisi: %s <onoma_arxiou>\n", argv[0]);
        return 1; // Έξοδος με κωδικό σφάλματος
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Το αρχείο %s δεν μπορεί να ανοίξει.\n", argv[1]);
        return 1; // Έξοδος με κωδικό σφάλματος
    }
    size=metritis_grammon(file);

    printf("\no arithmos ton grammon sto arxeio einai: %d\n", size);

    s1 = (struct antikimeno*)malloc(size * sizeof(antikimeno));
    s2 = (struct pinakas_komvon*)malloc(size2 * sizeof(pinakas_komvon));
    topothetisi_sthn_lista(file,s1,size);
    emfanisi_kiklomatikon_stoixion(s1,size);
   
    for(i=0;i<size;i++){
        found=0;
        
        for(j=0; j<size2;j++){
            if(strcmp((s1+i)->ypsilo_dinam,(s2+j)->onoma)==0){
                found=1;
            }
        }
        if(found!=1&& strcmp((s1+i)->ypsilo_dinam,"0")!=0){
            size2++;
            s2=realloc(s2, sizeof(pinakas_komvon)*size2);
            strcpy((s2+(j-1))->onoma,(s1+i)->ypsilo_dinam);
        }
        
    }
    for(i=0;i<size;i++){
        found=0;
        
        for(j=0; j<size2;j++){
            if(strcmp((s1+i)->xamilo_dinam,(s2+j)->onoma)==0){
                found=1;
            }
        }
        if(found!=1 && strcmp((s1+i)->xamilo_dinam,"0")!=0){
        
            size2++;
            s2=realloc(s2, sizeof(pinakas_komvon)*size2);
            strcpy((s2+(j-1))->onoma,(s1+i)->xamilo_dinam);  
            
            
            
        }
    }
    for(i=0; i<size; i++){
        if((s1+i)->onoma[0]==comparisonChar){
            size2++;
            s2=realloc(s2, sizeof(pinakas_komvon)*size2);
            strcpy((s2+(j-1))->onoma,(s1+i)->onoma);
            j++;

        }
    }
    size2--;
    s2=realloc(s2, sizeof(pinakas_komvon)*size2);

    size2= pinakas_komvon_sinartisi(s1,s2,size,size2);
    while(epilogi==-1){
        printf("solution with:\n 1. LxU method\n 2. Gauss-Seidel method\n 3. sparse arrays\n 0. exit\n choise:");
        scanf("%d", &epilogi);
        if(epilogi>3 || epilogi<1){
            if(epilogi!=0){
                epilogi=-1;
            }
            
        }
        else{
            methodos_sosti(file,size,s2,size2,s1,epilogi);
        }

    }
    
    free(s1);
    free(s2);
    fclose(file);

    return 0;
}

int metritis_grammon(FILE *file){
    char c;
    int size=1;
   while ((c = fgetc(file)) != EOF) {
        
        if (c == '\n') {
            size++;
           
        }
        
    } 
    return size;
}
void emfanisi_kiklomatikon_stoixion(struct antikimeno *s1,int size){
    char kombos[50];
    int i=0,fount=0;
    printf("dose mou ton kombo: ");
    scanf("%s", kombos);
    while(i<size){
        if(strcmp((s1+i)->xamilo_dinam,kombos)==0){
            printf("o kombos exei to stoixio: %s\n",(s1+i)->onoma);
            fount=1;
        }
        else if(strcmp((s1+i)->ypsilo_dinam,kombos)==0){
            printf("o kombos exei to stoixio: %s\n",(s1+i)->onoma);
            fount=1;
        }
        i++;
    }
    if(fount==0){
        printf("o kombos den exei kiklomatika stoixia poy na enonontai me auton\n");
    }


}
void topothetisi_sthn_lista(FILE *file, struct antikimeno *s1,int size){
    int i=0;
    fseek(file, 0, SEEK_SET);
    while (i<size) {
        
        fscanf(file, "%s %s %s %f ", (s1+i)->onoma,(s1+i)->ypsilo_dinam,(s1+i)->xamilo_dinam, &(s1+i)->timi);
        
        i++;
    }    

}
void ektiposi_kiklomatos(struct antikimeno *s1,int size){
    int i;
    printf("\n\nto kikloma einai\n\n");
    for(i=0;i<size;i++){
        
        printf("|onoma:%s | yd:%s | xd:%s | tm:%f |\n ", (s1+i)->onoma,(s1+i)->ypsilo_dinam,(s1+i)->xamilo_dinam,(s1+i)->timi);
    }
}
int pinakas_komvon_sinartisi(struct antikimeno *s1,struct pinakas_komvon *s2,int size,int size2){
    
   int i;
   printf("apo sinartisi\n");
    for(i=0;i<size2;i++){
        printf("size is : %d\n", size2);
        printf("%s\n", (s2+i)->onoma);
        printf("I=%d\n",i);
        printf("_______\n");
        
    }
    return size2;

}
void methodos_sosti(FILE *file, int size,struct pinakas_komvon *s2, int size2,struct antikimeno *s1,int epilogi){
    
    char onoma[50],ypdin[50],xd[50];
    float timi;
    float *arrayB= (float *)malloc(size2 *sizeof(float *));
    float **arrayA= (float **) malloc(size2 *sizeof(float*));
    int i=0,j=0,k=0,position_1=-1,position_2=-1,position_3=-1;
    if(arrayA==NULL){
        printf("h malloc den mporese na ekxorisi mnimi GIA PINAKA A");
        
    }
    for(i=0; i<size2; i++){
        arrayA[i]=(float *) malloc(size2*sizeof(float*));
        if(arrayA[i]==NULL){
            printf("h malloc den mporese na ekxorisi mnimi GIA PINAKA A");
            
        }
    }
    
    for(i=0;i<size2;i++){
        for(j=0; j<size2;j++){
            arrayA[i][j]=0;
        }
        
    }
    for(i=0;i<size2;i++){
        arrayB[i]=0;    
    }
    fseek(file, 0, SEEK_SET);
    
    for(i=0;i<size;i++){
        fscanf(file, "%s %s %s %f ", onoma,ypdin,xd, &timi);
        
        if(onoma[0]=='R'){
            for(j=0;j<size2;j++){
                if(strcmp(s2[j].onoma,ypdin)==0){
                    position_1=j;
                }
                else if(strcmp(s2[j].onoma,xd)==0){
                    position_2=j;
                }

            }
            if(strcmp(xd,"0")==0){
                arrayA[position_1][position_1]+=(1/timi);

            }
            else if(strcmp(ypdin,"0")==0){
                arrayA[position_2][position_2]+=(1/timi);
            }
            else{
                arrayA[position_1][position_1]+=(1/timi);
                arrayA[position_1][position_2]+=(-1/timi);
                arrayA[position_2][position_1]+=(-1/timi);
                arrayA[position_2][position_2]+=(1/timi);
            }
            
        }
        else if(onoma[0]=='V'){
            for(j=0; j<size2;j++){
                if(strcmp(s2[j].onoma,ypdin)==0){
                    position_1=j;
                }
                else if(strcmp(s2[j].onoma,xd)==0){
                    position_2=j;
                }
                else if(strcmp(s2[j].onoma,onoma)==0){
                    position_3=j;
                }
            }
            if(strcmp(xd,"0")==0){
                arrayA[position_3][position_1]=1;
                arrayA[position_1][position_3]=1;
            }
            else if(strcmp(ypdin,"0")==0){
                arrayA[position_3][position_2]=1;
                arrayA[position_2][position_3]=1;  
            }
            else{
                arrayA[position_3][position_1]=1;
                arrayA[position_1][position_3]=1;
                
                arrayA[position_3][position_2]=1;
                arrayA[position_2][position_3]=1;
            }
            
        }
        
    }


    fseek(file, 0, SEEK_SET);
    for(i=0; i<size; i++){
        fscanf(file, "%s %s %s %f ", onoma,ypdin,xd, &timi);
        if(onoma[0]=='I'){
            for(j=0; j<size2;j++){
                if(strcmp(ypdin,s2[j].onoma)==0){
                    arrayB[j]=-timi;
                }
                else if(strcmp(xd,s2[j].onoma)==0){
                    arrayB[j]=timi;
                }
                else{
                    arrayB[j]+=0;
                }
            }
        }
        else if(onoma[0]=='V'){
            for(j=0; j<size2; j++){
                if(strcmp(onoma,s2[j].onoma)==0){
                    arrayB[j]=timi;
                }
            }
        }
    }
    printf("pinakas apo thn sosti sinartisi\n");
    for(i=0;i<size2;i++){
        for(j=0; j<size2;j++){
            printf("|%f|",arrayA[i][j]);
        }
        printf("\n");
    }
    printf("\n\n pinakas b\n");
    for(i=0; i<size2;i++){
        printf("|%f|\n",arrayB[i]);
        
    }
    if(epilogi==1){
        methodos_LxU(arrayA,arrayB,size2);
    }
    else if(epilogi==2){
        methodos_gacobi_gauss_sieder(arrayA,arrayB,size2);
    }
    else{
        methodos_araion_pinakon(file,arrayB,s2,size2,size);
    }
        
    printf("\n\n");

    for (i = 0; i < size2; i++) {
        free(arrayA[i]);
    }
    free(arrayA);
    free(arrayB);

}
void methodos_LxU(float **arrayA,float *arrayB,int size2){
    int i,j;
    float *arrayY= (float *)malloc(size2 *sizeof(float *));
    float *arrayX= (float *)malloc(size2 *sizeof(float *));
    float **arrayL=(float **) malloc(size2 *sizeof(float*));
    float **arrayU=(float **) malloc(size2 *sizeof(float*));
    float factor;
    for(i=0; i<size2; i++){
        arrayL[i]=(float *) malloc(size2*sizeof(float*));
        if(arrayL[i]==NULL){
            printf("h malloc den mporese na ekxorisi mnimi GIA PINAKA L");
            
        }
    }
    for(i=0; i<size2; i++){
        arrayU[i]=(float *) malloc(size2*sizeof(float*));
        if(arrayU[i]==NULL){
            printf("h malloc den mporese na ekxorisi mnimi GIA PINAKA U");
            
        }
    }

    printf("\n apo thn lu sunartisi\n");
    for(i=0;i<size2;i++){
        for(j=0; j<size2;j++){
            printf("|%f|",arrayA[i][j]);
        }
        printf("\n");
    }
    printf("\n\n pinakas b\n");
    for(i=0; i<size2;i++){
        printf("|%f|\n",arrayB[i]);
        
    }
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size2; j++) {
            arrayU[i][j] = arrayA[i][j];
            if(i==j){
                arrayL[i][j]=1;
            }
            else{
                arrayL[i][j]=0;
            }
            //L[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    for (int k = 0; k < size2 - 1; k++) {
        for (int i = k + 1; i < size2; i++) {
            factor = arrayU[i][k] / arrayU[k][k];
            arrayL[i][k] = factor;
            for (int j = k; j < size2; j++) {
                arrayU[i][j] -= factor * arrayU[k][j];
            }
        }
    }
    printf("[L]: \n");
    for(i=0; i<size2; i++)
    {
        for(j=0; j<size2; j++)
            printf("|%f|",arrayL[i][j]);
        printf("\n");
    }
    printf("\n\n[U]: \n");
    for(i=0; i<size2; i++)
    {
        for(j=0; j<size2; j++)
            printf("|%f|",arrayU[i][j]);
        printf("\n");
    }
    for(i=0; i<size2; i++)
    {
        arrayY[i]=arrayB[i];
        for(j=0; j<i; j++)
        {
            arrayY[i]-=arrayL[i][j]*arrayY[j];
        }
    }
    printf("\n\n[Y]: \n");
    for(i=0; i<size2; i++)
    {
        printf("%f\n",arrayY[i]);
    }
    for(i=size2-1; i>=0; i--)
    {
        arrayX[i]= arrayY[i];
        for(j=i+1; j<size2; j++)
        {
            arrayX[i]-=arrayU[i][j]*arrayX[j];
        }
        arrayX[i]/=arrayU[i][i];
    }
    printf("\n\n[X]: \n");
    for(i=0; i<size2; i++){
        printf("%f\n",arrayX[i]);
    }

    
    
    for (i = 0; i < size2; i++) {
        free(arrayL[i]);
    }
    for (i = 0; i < size2; i++) {
        free(arrayU[i]);
    }
    free(arrayL);
    free(arrayU);
    free(arrayY);
    free(arrayX); 
}
void methodos_gacobi_gauss_sieder(float **arrayA,float *arrayB,int size2){
    //float arrayA[4][4];
    //float arrayB[4];
    float *arrayXold= (float *)malloc(size2 *sizeof(float *));
    float *arrayXnew= (float *)malloc(size2 *sizeof(float *));
    int i,j,h;
    float apostasi=0,s;
    FILE *new_file;
    new_file = fopen("arxeio_katagrafon.txt", "w");
    for(i=0;i<size2;i++){
        arrayXold[i]=0;
        arrayXnew[i]=0;
        
    }
    fprintf(new_file, "\n ");
    apostasi=10.0;
    fprintf(new_file, "%f \n",apostasi);
    //float s;
    while(apostasi>=0.0001) {
         apostasi = 0.0;
        //printf("mpika\n");
        for (int i = 0; i < size2; i++) {
            s = 0;
            for (int j = 0; j < size2; j++) {
                if (i != j) {
                    s += arrayA[i][j] * arrayXold[j];
                }
            }
            if(arrayA[i][i]!=0.0){
                arrayXnew[i] = (arrayB[i] - s) / arrayA[i][i];
            }
            else{
                arrayXnew[i]=0.0;
            }
            
            //printf("arrayXnew[%d]: %f\n", i, arrayXnew[i]);
        }

       
        for (int h = 0; h < size2; h++) {
            apostasi +=  abs(abs(arrayXnew[h])-abs(arrayXold[h]));
            //apostasi+= abs(apostasi);
            arrayXold[h] = arrayXnew[h];
            
        }
        fprintf(new_file, "%f\n ",apostasi);
        //printf("%f",apostasi);

    }
    fclose(new_file);
    // Εκτύπωση των τελικών τιμών
    printf("Solution:\n");
    for (int i = 0; i < size2; i++) {
        printf("X[%d] = %f\n", i, arrayXnew[i]);
    }


    free(arrayXold);
    free(arrayXnew);
}
void methodos_araion_pinakon(FILE *file, float *arrayB,struct pinakas_komvon *s2, int size2,int size ){
  cs *A; // Ο πίνακας A
    cs *B; // Ο πίνακας B
    cs *x; // Ο πίνακας x
    cs *c;
    int i,j,fount=0,success;
    char onoma[100],ypsilo_dinam[100],xamilo_dinam[100];
    float timi;
    FILE *new_file;
    new_file = fopen("example.txt", "w");
    
    double *arrayBnew; // Ένας πίνακας που περιέχει τα στοιχεία του πίνακα B
    fseek(file, 0, SEEK_SET);
    // Ανάθεση μνήμης για τον πίνακα B
    arrayBnew = (double*)malloc(size2 * sizeof(double));
    if (arrayBnew == NULL) {
        printf("Memory allocation failed for arrayB\n");
        
    }
    
    // Αντιγραφή των στοιχείων του πίνακα B στον νέο πίνακα διπλής ακρίβειας
    for (i = 0; i < size2; i++) {
        arrayBnew[i] = arrayB[i];
    }
    for(i=0;i<size;i++){
        fscanf(file, "%s %s %s %f ", onoma,ypsilo_dinam,xamilo_dinam, &timi);
        for(j=0;j<size2;j++){
            if(strcmp(ypsilo_dinam,s2[j].onoma)==0){
                fount=j+1;
            }
        }
        fprintf(new_file, "%d ",fount);
        fount=0;
        for(j=0;j<size2;j++){
            if(strcmp(xamilo_dinam,s2[j].onoma)==0){
                fount=j+1;
            }
        }
        fprintf(new_file, "%d ",fount);
        fprintf(new_file, "%f\n",timi);

    }
    
    fclose(new_file);
    
    new_file = fopen("example.txt", "r");
    // Φορτώστε τον πίνακα A από ένα αρχείο
    A = cs_load(new_file);
    //cs_triplet(A);
    
    if (A == NULL) {
        printf("Failed to load matrix A\n");
        free(arrayBnew);
        
    }
    
    
    // Ανάθεση μνήμης για τον πίνακα B
    //B = cs_spalloc(A->m, 1, size2, 1, 1);
    c = cs_spalloc(A->m,A->n,A->nzmax,1,1);
    
    // Δημιουργία ενός νέου πίνακα double και αντιγραφή των στοιχείων του πίνακα B
    double *arrayB_double = (double*)malloc(c->n * sizeof(double));
    if (arrayB_double == NULL) {
        printf("Memory allocation failed for arrayB_double\n");
        cs_spfree(A);
        cs_spfree(B);
        free(arrayBnew);
        return;
    }
    for (i = 0; i < c->n; i++) {
        arrayB_double[i] = arrayBnew[i];
    }
    printf("simio1\n");
    for (i = 0; i < c->n; i++) {
        printf("%f",arrayB_double[i]);
    }
    printf("\n------------------\n");
    
    cs_print(A,0);
    c=cs_triplet(A);
   // c = cs_compress(A); // kanei ton pinaka simpiknomeno
    printf("simio1.5\n");
    cs_print(c,0);
    success =cs_lusol(c, arrayB_double,0,0.001);
    printf("simio2\n");
    if (success != 1) {
        printf("Failed to solve the system Ax = B\n");
        cs_spfree(A);
        cs_spfree(B);
        cs_spfree(x);
        free(arrayBnew);
        free(arrayB_double);
    
    }
    else{
        for(i=0;i<c->n;i++){
            printf("%lf\n ",arrayB_double[i]);
        }
        // Απελευθέρωση μνήμης
        cs_spfree(A);
        cs_spfree(B);
        cs_spfree(x);
        free(arrayBnew);
        free(arrayB_double);
    }

}
