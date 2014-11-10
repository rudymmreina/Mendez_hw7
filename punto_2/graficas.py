import numpy as np
import matplotlib.pyplot as plt
import sys

d=sys.argv[1]

datos = np.loadtxt(d)


x= datos[:,0]
u= datos[:,1]
p= datos[:,2]
rho= datos[:,3]


f, axarr = plt.subplots(3, sharex=True)
axarr[0].plot(x, u, 'y-')
axarr[0].set_title("Velocidad")
axarr[0].set_ylabel('v [m/s]')

axarr[1].plot(x, p,'r-')
axarr[1].set_title("Presion")
axarr[1].set_ylabel('P [kPa]')

axarr[2].plot(x, rho,'g-')
axarr[2].set_title("Densidad")
axarr[2].set_xlabel('x [m]')
axarr[2].set_ylabel('rho [Kg/m^3]')

plt.savefig('estado_t.pdf')
plt.close()
