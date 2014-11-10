import numpy as np
import matplotlib.pyplot as plt
import sys

d=sys.argv[1]

datos = np.loadtxt(d)


u= datos[0]
p= datos[5]
d= datos[80]

f, axarr = plt.subplots(3, sharex=True)
axarr[0].plot(u, 'y-')
axarr[0].set_title("cuerda t=0")
axarr[0].set_ylabel('y [m]')
axarr[1].plot(p,'r-')
axarr[1].set_title("cuerda t=30")
axarr[1].set_ylabel('y [m]')
axarr[2].plot(d,'g-')
axarr[2].set_title("cuerda t=80")
axarr[2].set_xlabel('x [m]')
axarr[2].set_ylabel('y [m]')

plt.savefig('cuerda_rho.pdf')
plt.close()
