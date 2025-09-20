import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Provided data
data = {
    'Temp': [25, 29.3, 34.6, 37.5, 40.5, 44.2, 49.4, 55.7, 61.1, 66.3],
    'R': [10000, 8260, 7125, 6350, 5740, 5160, 4080, 3704, 2995, 2520],
    'Vout': [2.5, 2.63, 2.69, 2.77, 2.85, 2.91, 2.97, 3.05, 3.11, 3.19]
}

df = pd.DataFrame(data)

X = df['Temp'].values.reshape(-1, 1)
y = df['Vout'].values

# Linear regression
model = LinearRegression()
model.fit(X, y)
predicted_voltages = model.predict(X)

print("Intercept:", model.intercept_)
print("Coefficient:", model.coef_[0])

# Plot results
plt.scatter(df['Temp'], df['Vout'], color='blue', label='Actual')
plt.plot(df['Temp'], predicted_voltages, color='red', label='Predicted')
plt.title('Linear Regression: Voltage vs Temperature')
plt.xlabel('Temperature (°C)')
plt.ylabel('Voltage (V)')
plt.legend()
plt.show()
