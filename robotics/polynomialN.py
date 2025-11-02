import os
import pandas as pd
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

# Get the folder where this script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Build the full path to your CSV
csv_path = os.path.join(script_dir, "shootingSolutions2.csv")

# Load the CSV
df = pd.read_csv(csv_path)

# Separate inputs and outputs
X = df[['distance','radialVelocity']].values  # Distance, Radial Velocity
y_velocity = df['solutionVelocity'].values  # Solution Velocity
y_angle = df['solutionAngle'].values     # Solution Angle

# Degree of polynomial
n = 4

# Generate polynomial features
poly = PolynomialFeatures(degree=n, include_bias=True)
X_poly = poly.fit_transform(X)

# Fit polynomial for velocity
model_velocity = LinearRegression()
model_velocity.fit(X_poly, y_velocity)

# Fit polynomial for angle
model_angle = LinearRegression()
model_angle.fit(X_poly, y_angle)

# Get feature names
terms = poly.get_feature_names_out(['x','y'])

# Function to print polynomial nicely
def print_polynomial(model, terms, intercept_name="f(x,y)"):
    coeffs = model.coef_
    intercept = model.intercept_
    equation = f"{intercept:.4f}"
    for c, t in zip(coeffs[1:], terms[1:]):  # skip bias term
        equation += f" + ({c:.4f})*{t}"
    print(f"{intercept_name} = {equation}\n")

# Print both polynomials
print_polynomial(model_velocity, terms, "Solution Velocity")
print_polynomial(model_angle, terms, "Solution Angle")
