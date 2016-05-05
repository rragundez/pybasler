#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import basler_camera as bc

frame_bytes = bc.capture()
frame_array = np.fromstring(frame_bytes, dtype=np.uint8)

try:
    frame = np.reshape(frame_array, (1080, -1, 3))
    print("Frame Captured Succesfully")
    plt.imshow(frame)
    plt.axis("off")
    plt.title("Hello from the Basler Camera through Python!")
    plt.show()
except Exception as e:
    print("Cannot Reshape: ", e)
