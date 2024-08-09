import numpy as np
from framework import file_m2k
import matplotlib
from tqdm import tqdm
from bisect import bisect
matplotlib.use('TkAgg')
from scipy.signal import hilbert
import matplotlib.pyplot as plt
from framework.post_proc import envelope

import time

experiment_root = "/home/gustavopadovam/ENSAIOS/FMC_furo.m2k"
experiment_ref = ""
dados = file_m2k.read(experiment_root + experiment_ref, type_insp='contact', water_path=0, freq_transd=5,
                      bw_transd=0.5, tp_transd='gaussian', sel_shots=0)

ascans_data = dados.ascan_data
sampling_frequency_MHz = dados.inspection_params.sample_freq * 1e6
initial_sample_times_microsec = dados.inspection_params.gate_start * 1e-6
element_positions_mm = dados.probe_params.elem_center[:, 0]

sampling_time = 1 / sampling_frequency_MHz

resol = "200x200"
x_roi, z_roi = np.load(f'/home/gustavopadovam/roi_times_padovam/roi_R70toR48_ang90_quad_Olympus_{resol}.npy')*1e3
times = np.load(f'/home/gustavopadovam/roi_times_padovam/times_quad_Olympus_{resol}.npy')*1e6


def tfm (times, x_roi, z_roi):
    size = int(np.sqrt(len(x_roi)) * np.sqrt(len(z_roi)))
    tfm_image = np.zeros(size)# Cria matriz do tamanho
    resolution = (int(np.sqrt(len(x_roi))), int(np.sqrt(len(z_roi))))

    for i in tqdm(range(64)):  # Loop percorrendo os transmissores
        for j in range(64):
            # Loop percorrendo os receptores
            time1 = times[:, i]
            time2 = times[:, j]
            tof = time1 + time2
            idx = (tof - dados.inspection_params.gate_start) / dados.inspection_params.sample_time
            for k in range(size):
                if idx[k] <= dados.ascan_data.shape[0]:
                    tfm_image[k] += ascans_data[int(idx[k]), i, j]
    tfm_image = tfm_image.reshape((resolution))
    return tfm_image

start_time = time.time()
print(f'A script demorou {time.time() - start_time:.2f}s para terminar!')


tfm_image = tfm(times, x_roi, z_roi)
tfm_image /= np.abs(tfm_image).max()


extent = (-45, 45, 48.0, 70.0)
plt.figure()
plt.imshow(np.log10(envelope(tfm_image)+1e-3), aspect="auto", extent= extent)
plt.title('TFM by Ray tracing times')
plt.xlabel('Angle [degress]')
plt.ylabel('y [mm]')
