import cv2
import numpy as np
import csv
import pickle
import matplotlib.pyplot as plt
import os

features_directory = '/content/data/'
labels_file = '/content/data/driving_log.csv'


def preprocess(img):
    resized = cv2.resize((cv2.cvtColor(img, cv2.COLOR_RGB2HSV))[:, :, 1], (40, 40))
    return resized


def data_loading(delta):
    logs = []
    features = []
    labels = []
    with open(labels_file, 'rt') as f:
        reader = csv.reader(f)
        for line in reader:
            logs.append(line)
        log_labels = logs.pop(0)

    for i in range(len(logs)):
        for j in range(3):
            img_path = logs[i][j]
            if 'IMG' in img_path:
                eff_path = img_path.split('IMG')
                img_path = features_directory + 'IMG' + eff_path[1]
            else:
                continue
            if os.path.exists(img_path):
                img = plt.imread(img_path)
                features.append(preprocess(img))
                if j == 0:
                    labels.append(float(logs[i][3]))
                elif j == 1:
                    labels.append(float(logs[i][3]) + delta)
                else:
                    labels.append(float(logs[i][3]) - delta)
            else:
                continue
            
    return features, labels


delta = 0.2
features, labels = data_loading(delta)

features = np.array(features).astype('float32')
labels = np.array(labels).astype('float32')

with open("features_40", "wb") as f:
    pickle.dump(features, f, protocol=4)
with open("labels", "wb") as f:
    pickle.dump(labels, f, protocol=4)
