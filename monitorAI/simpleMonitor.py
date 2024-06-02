import math
import random
from enum import Enum
import psutil
import subprocess
import time

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F


SLICE_IN_SECS = 1

p = subprocess.Popen("echo")
result_table = []
while p.poll() == None:
    result_table.append(psutil.Process(p.pid).memory_info())
    time.sleep(SLICE_IN_SECS)
print(result_table)