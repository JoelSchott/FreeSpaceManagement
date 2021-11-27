import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

RESULTS_DATA_PATH = 'C:\\Users\\joels\\Documents\\MST\\CS_3800\\Free Space Management Project\\FreeSpaceManagement\\results\\experiment_results.csv'

results = pd.read_csv(RESULTS_DATA_PATH)

algs = ['Best Fit', 'Worst Fit', 'First Fit', 'Next Fit']
metrics = ['Total Hole Checks', 'Number of Failed Allocations', 'Total Wait Time', 'Average Usage']
for metric in metrics:
  plt.title(f"{metric} by Algorithm")
  plt.bar(range(len(algs)), [np.mean(results[results['Algorithm'] == alg][metric]) for alg in algs])
  plt.xlabel("Space Management Algorithm")
  plt.ylabel(f"Average {metric}")
  plt.xticks(range(len(algs)), algs)
  plt.savefig(f'C:\\Users\\joels\\Documents\\MST\\CS_3800\\Free Space Management Project\\FreeSpaceManagement\\results\\Average {metric}.png')
  plt.close('all')
