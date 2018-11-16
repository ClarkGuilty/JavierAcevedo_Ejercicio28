#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov 16 00:19:35 2018

@author: Javier Alejandro Acevedo Barroso
"""


import numpy as np
import matplotlib.pyplot as plt

real = 7./6.

datos = np.loadtxt("rta.txt")
x = np.power(10,datos[:,0])
y = datos[:,1]

plt.plot(x,np.abs(y-real)*100/real)
plt.loglog()
plt.xlabel("$N_{puntos}$")
plt.ylabel("Diferencia porcentual Monte Carlo vs. Analitica")
plt.savefig("ej28")