#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nx 100
#define nt 12000

int main(int argc, char **argv){

  //definiendo las variables
  int   i,j,k,a,b,d,n,m,s;
  float x_max,x_min,t_max,t_min,dx,dt,ds,L,c,T,rho,r;
  double t;
  float x[nx+1],u[nx+1],u_p[nx+1],u_new[nx+1],l[121];

  //constantes
  T=40; //[N]
  L=100; //[m]
  rho=atof(argv[1]); //[Kg/m]

  c=sqrt(T/rho);//[m/s]
  t=0;
  //intervalos de integracion y numero de pasos
  x_max=L;//[m]
  x_min=0;//[m]
  t_max=120;//[s]
  t_min=0;//[s]


  dx=(x_max-x_min)/nx;
  dt=30;
  ds=(t_max-t_min)/nt;
  //printf("%f %f \n", dx, dt); //prueba

  r=(1/c)*(dt/dx);
  //printf("%f \n", r); //prueba
  for(i=0;i<(nx+1);i++){
    x[i]=x_min+(i*dx); //[m]
    if(x[i]<=(0.8*L)){
      u[i]=1.25*(x[i]/L);
    }
    else{
      u[i]=5-(5*(x[i]/L));
    }
    //printf("%f %f\n", x[i], u[i]); //prueba
  }

  for(j=0;j<121;j++){
    l[j]=j;
  }


  //ESCRIBIENDO LOS DATOS

  FILE *in;
  char filename[20]="string_rho.dat";
  printf("Writing to file: %s\n", filename);
  //opens the file, writes, closes the file
  in = fopen(filename,"w");
  if(!in){
    printf("problems opening the file %s\n", filename);
    exit(1);
  }

  //escribiendo
  for(k=0;k<(nx+1);k++){
    u_p[k]=u[k];
    //printf("%f\n", u_p[k]);
    fprintf(in,"%f ",u_p[k]);
  }
  fprintf(in,"\n");

  for(a=1;a<(nt+1);a++){
    t=(a*ds);
    //printf("%f\n",t);

    for(b=1;b<(nx);b++){
      u_new[b]=u_p[b]+((0.5*pow(r,2))*(u_p[b+1]-(2*u_p[b])+u_p[b-1]));
    }
    for(d=0;d<(nx+1);d++){
      u_p[d]=0;
    }
//    fprintf(in,"%f ",u_p[0]);
    for(n=1;n<nx;n++){
      u_p[n]=u_new[n];
    //  fprintf(in,"%f ",u_p[n]);
    }
  //  fprintf(in,"%f \n",u_p[nx+1]);*/

   for(m=1;m<121;m++){
      if((t>(l[m]-0.00001))&(t<(l[m]+0.00001))){
        //printf("%f\n",t);
        for(s=0;s<(nx+1);s++){
        //  printf("%f ",u_p[s]);
          fprintf(in,"%f ",u_p[s]);
        }
        //printf("\n");
        fprintf(in,"\n");
      }
    }
  }

  fclose(in);

  return 0;
}
