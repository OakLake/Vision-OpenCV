# Kalman filter
# Sammy Hasan
# 2017


import math as m
import numpy as np
import matplotlib.pyplot as plt
import os

os.system('clear')


# parameters
timesteps = 1000
period = 200
mu = 0
sigma = 0.25
sigma_k = 0.01

sigma_proc = 0.001
freq_factor = 0.008

TruData = []
simData = []
kalmanData = []


def sqr_wave(t,period):
    return 1 if (t%period) < period/2 else 0
def saw_wave(t,period):
    return t%period

def compute_kalman(t,msr,cov,pre):

    next_pred = pre + sigma_k**2
    cov = cov + sigma_proc

    gain = cov / (cov + sigma**2)

    next_pred = next_pred + gain*(msr - next_pred)
    cov = (1 - gain) * cov
    return cov,next_pred

c = sigma_k
k = 0
for t in range(timesteps):

    sig = np.random.normal(mu,sigma)
    tr_sin = sqr_wave(t,period) + m.sin(freq_factor*t)

    d = tr_sin + sig
    c,k = compute_kalman(t,d,c,k)

    simData.append(d)
    kalmanData.append(k)
    TruData.append(tr_sin)



print('## DONE ##')

plt.plot(list(range(timesteps)),simData,label='Raw wave')
plt.plot(list(range(timesteps)),kalmanData,label='Kalman wave')
plt.plot(list(range(timesteps)),TruData,label='True wave')
plt.legend(loc='upper right')

plt.show()
