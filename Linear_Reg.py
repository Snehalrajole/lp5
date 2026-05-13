Linear Regression
# ==========================================================
# Boston House Price Prediction
# Using Linear Regression and Deep Neural Network
# ==========================================================

# ================= IMPORT LIBRARIES =================

import numpy as np
import pandas as pd
import tensorflow as tf

from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import r2_score

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# ================= LOAD DATASET =================

print("Loading Boston Housing Dataset...\n")

boston = fetch_openml(
    name="boston",
    version=1,
    as_frame=True
)

# Full dataset
data = boston.frame

# ================= DISPLAY DATASET =================

print("Dataset Shape :", data.shape)

print("\nFirst 5 Rows:\n")

print(data.head())

# ================= SELECT FEATURES =================

# Input Features
X = data[['LSTAT', 'RM', 'PTRATIO']]

# Output Target
y = data['MEDV']

# ================= TRAIN TEST SPLIT =================

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.20,
    random_state=42
)

print("\nTraining Data Shape :", X_train.shape)

print("Testing Data Shape  :", X_test.shape)

# ================= FEATURE SCALING =================

scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)

X_test = scaler.transform(X_test)

# ==========================================================
# LINEAR REGRESSION MODEL
# ==========================================================

lr_model = LinearRegression()

# Train model
lr_model.fit(X_train, y_train)

# Prediction
y_pred_lr = lr_model.predict(X_test)

# ================= EVALUATION =================

print("\n===== Linear Regression Result =====")

print("MSE :", mean_squared_error(y_test, y_pred_lr))

print("MAE :", mean_absolute_error(y_test, y_pred_lr))

print("R2 Score :", r2_score(y_test, y_pred_lr))

# ==========================================================
# DEEP NEURAL NETWORK MODEL
# ==========================================================

model = Sequential()

# Input + Hidden Layer 1
model.add(
    Dense(
        128,
        activation='relu',
        input_shape=(3,)
    )
)

# Hidden Layer 2
model.add(Dense(64, activation='relu'))

# Hidden Layer 3
model.add(Dense(32, activation='relu'))

# Hidden Layer 4
model.add(Dense(16, activation='relu'))

# Output Layer
model.add(Dense(1))

# ================= MODEL SUMMARY =================

print("\n===== Neural Network Summary =====\n")

model.summary()

# ================= COMPILE MODEL =================

model.compile(
    optimizer='adam',
    loss='mse',
    metrics=['mae']
)

# ================= TRAIN MODEL =================

print("\nTraining Started...\n")

history = model.fit(
    X_train,
    y_train,
    epochs=50,
    batch_size=16,
    validation_split=0.1,
    verbose=1
)

# ================= EVALUATE MODEL =================

loss, mae = model.evaluate(X_test, y_test)

print("\n===== Neural Network Result =====")

print("MSE :", loss)

print("MAE :", mae)

# ================= PREDICTION =================

new_data = pd.DataFrame(
    [[5.0, 6.5, 15.0]],
    columns=['LSTAT', 'RM', 'PTRATIO']
)

# Scale new data
new_data_scaled = scaler.transform(new_data)

# Predict house price
prediction = model.predict(new_data_scaled)

print("\nPredicted House Price :")

print(prediction[0][0])