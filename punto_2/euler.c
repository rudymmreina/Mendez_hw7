#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nx 2000
#define nt 500
#define g 1.4


float func_F1(float u1,float u2,float u3);
float func_F2(float u1,float u2,float u3);
float func_F3(float u1,float u2,float u3);
float U_medio(float Ui1,float Ui,float Fi1,float Fi,float dx,float dt);
float U_new(float U,float F_medioi1,float F_medioi,float dx,float dt);

int main(void){

  //definiendo las variables
  int   i,j;
  float x_max,x_min,t_max,t_min,dx,dt,t;
  float  x[nx],rho[nx],u[nx],p[nx],et[nx],U_1[nx],U_2[nx],U_3[nx],F_1[nx],F_2[nx],F_3[nx];
  float Umedio_1[nx],Umedio_2[nx],Umedio_3[nx],Fmedio_1[nx],Fmedio_2[nx],Fmedio_3[nx];
  float Unew_1[nx],Unew_2[nx],Unew_3[nx],Fnew_1[nx],Fnew_2[nx],Fnew_3[nx];
  float x_new[nx],rho_new[nx],u_new[nx],p_new[nx],et_new[nx];

  //intervalos de integracion y numero de pasos
  x_max=10;
  x_min=-10;
  t_max=0.1;
  t_min=0;

  //precision
  dx=(x_max-x_min)/nx;
  dt=(t_max-t_min)/nt;
  //printf("%f %f \n",dx,dt); //prueba
  //matrices de condiciones iniciales
  for(i=0;i<nx;i++){
    x[i]=x_min+(i*dx); //[m]
    u[i]=0;          //[m/s]
    if(x[i]<0){
      rho[i]=1; //[kg/m3]
      p[i]=100;//[KPa]
    }
    else{
      rho[i]=0.125;//[kg/m3]
      p[i]=10;//[KPa]
      }
  et[i]=(1/rho[i])*(((p[i])/(g-1))+(((rho[i])*(pow(u[i],2)))/(2)));

  //printf("%f %f %f %f %f\n", x[i], u[i], rho[i], p[i], et[i]); //prueba
  }

  //definiendo el vector U

  for(i=0;i<nx;i++){
    U_1[i]=rho[i];
    U_2[i]=rho[i]*u[i];
    U_3[i]=rho[i]*et[i];
    //printf("%f %f %f \n", U_1[i], U_2[i], U_3[i]); //prueba
  }

  //definiendo el vector F

  for(i=0;i<nx;i++){
    F_1[i]=func_F1(U_1[i],U_2[i],U_3[i]);
    F_2[i]=func_F2(U_1[i],U_2[i],U_3[i]);
    F_3[i]=func_F3(U_1[i],U_2[i],U_3[i]);
  //  printf("%f %f %f \n", F_1[i], F_2[i], F_3[i]); //prueba
  }

//METODO DE RITCHMEYER
  for(j=1;j<(nt+1);j++){
    t=0;
    t=t+(dt*j);
  //  printf("%f \n", t);
    for(i=0;i<(nx-1);i++){
      Umedio_1[i]=U_medio(U_1[i+1],U_1[i],F_1[i+1],F_1[i], dx, dt);
      Umedio_2[i]=U_medio(U_2[i+1],U_2[i],F_2[i+1],F_2[i], dx, dt);
      Umedio_3[i]=U_medio(U_3[i+1],U_3[i],F_3[i+1],F_3[i], dx, dt);
      Fmedio_1[i]=func_F1(Umedio_1[i],Umedio_2[i],Umedio_3[i]);
      Fmedio_2[i]=func_F2(Umedio_1[i],Umedio_2[i],Umedio_3[i]);
      Fmedio_3[i]=func_F3(Umedio_1[i],Umedio_2[i],Umedio_3[i]);
    }
    for(i=1;i<(nx-1);i++){
      Unew_1[i]=U_new(U_1[i],Fmedio_1[i],Fmedio_1[i-1],dx,dt);
      Unew_2[i]=U_new(U_2[i],Fmedio_2[i],Fmedio_2[i-1],dx,dt);
      Unew_3[i]=U_new(U_3[i],Fmedio_3[i],Fmedio_3[i-1],dx,dt);
      Fnew_1[i]=func_F1(Unew_1[i],Unew_2[i],Unew_3[i]);
      Fnew_2[i]=func_F2(Unew_1[i],Unew_2[i],Unew_3[i]);
      Fnew_3[i]=func_F3(Unew_1[i],Unew_2[i],Unew_3[i]);
      U_1[i]=Unew_1[i];
      U_2[i]=Unew_2[i];
      U_3[i]=Unew_3[i];
      F_1[i]=Fnew_1[i];
      F_2[i]=Fnew_2[i];
      F_3[i]=Fnew_3[i];
      //printf("%f %f %f \n",U_1[i],U_2[i],U_3[i]); //prueba
    }

  }

//ESCRIBIENDO LOS DATOS

  FILE *in;
  char filename[nx]="condiciones_iniciales.dat";
  printf("Writing to file: %s\n", filename);
  /*opens the file, writes, closes the file*/
  in = fopen(filename,"w");
  if(!in){
    printf("problems opening the file %s\n", filename);
    exit(1);
  }
  for(i=0;i<nx;i++){
    fprintf(in,"%f %f %f %f\n",x[i],u[i],p[i],rho[i]);
  }
  fclose(in);


//generando los nuevos datos de presion, veloscidad y densidad
  for(i=0;i<(nx);i++){
    x_new[i]=x[i];
    rho_new[i]=U_1[i];
    u_new[i]=U_2[i]/U_1[i];
    et_new[i]=U_3[i]/U_1[i];
    p_new[i]=(g-1)*((rho_new[i]*et_new[i])-(0.5*rho_new[i]*pow(u_new[i],2)));

  //  printf("%f %f %f %f %f\n",x_new[i], rho_new[i], u_new[i], et_new[i],p_new[i]); //prueba
  }

//ESCRIBIENDO LOS DATOS

  FILE *in2;
  char filename2[nx]="estado_t.dat";
  printf("Writing to file: %s\n", filename2);
  /*opens the file, writes, closes the file*/
  in2 = fopen(filename2,"w");
  if(!in2){
    printf("problems opening the file %s\n", filename2);
    exit(1);
  }
  for(i=0;i<nx;i++){
    fprintf(in2,"%f %f %f %f\n",x_new[i],u_new[i],p_new[i],rho_new[i]);
  }
  fclose(in2);

  return 0;

}





float func_F1(float u1,float u2,float u3){
  double f1;
  f1=u2;
  return f1;
}

float func_F2(float u1,float u2,float u3){
  float f2;
  f2=((pow(u2,2))/(u1))+((g-1)*((u3)-((pow(u2,2))/(2*u1))));
  return f2;
}
float func_F3(float u1,float u2,float u3){
  float f3;
  f3=((u3)+((g-1)*((u3)-((pow(u2,2))/(2*u1)))))*(u2/u1);
  return f3;
}


float U_medio(float Ui1,float Ui,float Fi1,float Fi,float dx,float dt){
  float U_medio;
  U_medio=(0.5*(Ui1+Ui))-(0.5*(dt/dx)*(Fi1-Fi));
  return U_medio;
}


float U_new(float U,float F_medioi1,float F_medioi,float dx,float dt){
  float U_new;
  U_new=U-((dt/dx)*(F_medioi1-F_medioi));
  return U_new;
}
