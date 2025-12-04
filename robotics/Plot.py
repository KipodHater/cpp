import numpy as np
import plotly.graph_objects as go

X = np.linspace(-2, 2, 100)
Y = np.linspace(0, 8, 100)
y, x = np.meshgrid(Y, X)

Z_height =   90.3059 + (-11.9145)*x + (9.1680)*y + (1.2005)*x**2 + (-0.7879)*x*y + (0.2854)*y**2 + (-0.0536)*x**3 + (0.0144)*x**2*y + (0.0145)*x*y**2 + (-0.0046)*y**3
Z_heat = 6.3048 + (0.1467)*x + (-0.0675)*y + (0.0915)*x**2 + (-0.1489)*x*y + (0.0721)*y**2 + (-0.0055)*x**3 + (0.0090)*x**2*y + (-0.0065)*x*y**2 + (0.0026)*y**3

fig = go.Figure(data=[go.Surface(
    z=Z_height, 
    x=X, 
    y=Y,
    surfacecolor=Z_heat,   # color by heat
    colorscale='Viridis'
)])

fig.update_layout(scene=dict(
                    xaxis_title='X',
                    yaxis_title='Y',
                    zaxis_title='Height'),
                  width=800, height=600)
fig.show()
