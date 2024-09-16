#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

void cevap_anahtari_uret(char cevap_anahtari[ ], int S){
    int i;
    for(i=0;i<S;i++){
        cevap_anahtari[i]=rand()%5+65;
    }
    cevap_anahtari[i]='\0';
}
void cevap_anahtari_yazdir(char cevap_anahtari[ ], int S){
    int i,sayac=0;
    printf("\n Cevap Anahtari: \n");
    for(i=0;i<S;i++,sayac++){
        if(sayac==10){
            printf("\n");
            sayac=0;
        }
        printf("%.2d. soru %c | ",i+1,cevap_anahtari[i]);
    }
    printf("\n");
}

void sinavi_uygula(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], int N, int S, double B,double D){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<S;j++){
            int rastgele=rand()%100;
            if(rastgele<B*100){
                ogrenci_cevaplari[i][j]='X';
            }
            else if(rastgele<D*100){
                ogrenci_cevaplari[i][j]=cevap_anahtari[j];
            }
            else{
                char temp=cevap_anahtari[j];
                while(temp==cevap_anahtari[j]){
                    temp=rand()%5+65;
                }
                ogrenci_cevaplari[i][j]=rand()%5+65;
            }
        }
        ogrenci_cevaplari[i][j]='\0';//ogrenci cevaplari dizisini string yapmak icin
    }
}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[ ][100], int N, int S){
    int i,j,sayac=0;
    for(i=0;i<N;i++){
        printf("\n%d. ogrencinin cevaplari:\n",i+1);
        for(j=0;j<S;j++,sayac++){
            if(sayac==10){
                printf("\n");
                sayac=0;
            }
            printf("%.2d. soru :%c ",j+1,ogrenci_cevaplari[i][j]);
        }
        printf("\n");
        }
}
void ogrencileri_puanla(char ogrenci_cevaplari[ ][100], char cevap_anahtari[ ], double HBN[ ],int N, int S){
    int i,j;

    for(i=0;i<N;i++){
        int dogru_sayisi=0, yanlis_sayisi=0, bos_sayisi=0;
        double puan=0, net=0;
        for(j=0;j<S;j++){
            if(ogrenci_cevaplari[i][j]==cevap_anahtari[j]){
                dogru_sayisi++;
            }
            else if(ogrenci_cevaplari[i][j]=='X'){
                bos_sayisi++;
            }
            else{
                yanlis_sayisi++;
            }
        }
        net=S-((yanlis_sayisi*1.25)+bos_sayisi);
        puan=(100/(double)S)*net;
        if(puan<0){
            HBN[i]=0;
        }else{
           HBN[i]=puan;
        }
    }
}

double sinif_ortalamasi_hesapla(double HBN[ ], int N){
    int i;
    double toplam=0;
    for(i=0;i<N;i++){
        toplam=toplam+HBN[i];
    }
    return toplam/N;
}

double standart_sapma_hesapla(double ortalama, double HBN[ ], int N){
    int i;
    double toplam=0;
    for(i=0;i<N;i++){
        toplam=toplam+pow(HBN[i]-ortalama,2);
    }
    return sqrt(toplam/N);
}

void T_skoru_hesapla(double ortalama, double HBN[ ], int N, double std, double T_skoru[ ]){
    int i;
    for(i=0;i<N;i++){
        if(std==0)
            printf("Standart sapma 0 oldugu icin T skoru hesaplanamaz! \n");
        else 
        T_skoru[i]=60+10*((HBN[i]-ortalama)/std);
    }
}

int sinif_seviyesi_hesapla(double T_skoru[ ], int N){
    int i;
    double toplam=0;
    for(i=0;i<N;i++){
        toplam=toplam+T_skoru[i];
    }
    return toplam/N;
}
int seviye(double sinif_tskor_ortalama){
    if(sinif_tskor_ortalama>80){
        printf("Sinif Düzeyi: Üstün Basari \n");
        return 1;
    }
    else if(sinif_tskor_ortalama>70 && sinif_tskor_ortalama<=80){
        printf("Sinif Düzeyi: Mükemmel \n");
        return 2;
    }
    else if(sinif_tskor_ortalama>62.5 && sinif_tskor_ortalama<=70){
        printf("Sinif Düzeyi: Cok Iyi \n");
        return 3;
    }
    else if(sinif_tskor_ortalama>=57.5 && sinif_tskor_ortalama<=62.5){
        printf("Sinif Düzeyi: Iyi \n");
        return 4;
    }
    else if (sinif_tskor_ortalama>=52.5 && sinif_tskor_ortalama<=57.5){
        printf("Sinif Düzeyi: Ortanin Ustu \n");
        return 5;
    }
    else if (sinif_tskor_ortalama>=47.5 && sinif_tskor_ortalama<=52.5){
        printf("Sinif Düzeyi: Orta\n");
        return 6;
    }
    else if (sinif_tskor_ortalama>=42.5 && sinif_tskor_ortalama<=47.5){
        printf("Sinif Düzeyi: Zayif \n");
        return 7;
    }
       else {
        printf("Sinif Düzeyi: Kotu \n");
        return 8;
       }
    }
            
    void bilgileri_goster(double HBN[],double T_skoru[],int N,int sinif_seviye){
        int i;
        for(i=0;i<N;i++){
           printf("%d. ogrencinin HBN notu: %.2lf,T-skoru: %.2lf,harf notu:  ",i+1,HBN[i],T_skoru[i]);
             // harf_notu(N,T_skoru[i],sinif_seviye);
                printf("\n");
        }
    }

int main(){
    srand(time(NULL));
    int N, S;
    double B, D;
    char cevap_anahtari[100];
    char ogrenci_cevaplari[100][100];
    printf("Sinavda kac ogrenci var? (MAX 100 OGRENCi) \n ");
    scanf("%d", &N);
    if(N>100){
        printf("100'den fazla ogrenci giremezsiniz! \n");
        return 0;
    }
    printf("Sinavda kac soru var? (MAX 100 SORU) \n ");
    scanf("%d", &S);
    if(S>100){
        printf("100'den fazla soru giremezsiniz! \n");
        return 0;
    }
    printf("bos birakma ihtimali? (0 iLE 1 ARALIGINDA) \n");
    scanf("%lf", &B);
    if(B>1 || B<0){
        printf("0 ile 1 arasinda bir deger giriniz! \n");
        return 0;
    }
    printf("dogru cevap ihtimali? (0 iLE 1 ARALIGINDA) \n " );
    scanf("%lf", &D);
    if(D>1 || D<0){
        printf("0 ile 1 arasinda bir deger giriniz! \n");
        return 0;
    }
    
    cevap_anahtari_uret(cevap_anahtari, S);
    printf("\nCevap anahtari: \n\n ");
    cevap_anahtari_yazdir(cevap_anahtari, S);
    sinavi_uygula(ogrenci_cevaplari, cevap_anahtari, N, S, B, D);
    printf("\n sinav sonuclari:\n\n ");
    ogrenci_cevabini_yazdir(ogrenci_cevaplari, N, S);
    double HBN[100];
    ogrencileri_puanla(ogrenci_cevaplari, cevap_anahtari, HBN, N, S);
    double ortalama=sinif_ortalamasi_hesapla(HBN, N);
    double std=standart_sapma_hesapla(ortalama, HBN, N);
    double T_skoru[100];
    T_skoru_hesapla(ortalama, HBN, N, std, T_skoru);
    printf("\nortalama: %lf | standart sapma: %lf \n\n", ortalama, std);
    double sinif_tskor_ortalama=sinif_seviyesi_hesapla(T_skoru, N);
    int sinif_seviye=seviye(sinif_tskor_ortalama);
    //sinif_harf_notlari(N, T_skoru, sinif_seviyesi);
	bilgileri_goster(HBN,T_skoru,N,sinif_seviye);
    return 0;
}