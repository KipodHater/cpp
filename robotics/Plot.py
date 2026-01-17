import numpy as np
import plotly.graph_objects as go

X = np.linspace(-2, 2, 100)
Y = np.linspace(0, 8, 100)
y, x = np.meshgrid(X, Y)

Z_height =   89.4863 + (-9.3261)*x + (8.5226)*y + (0.5755)*x**2 + (-0.4571)*x*y + (0.1192)*y**2 + (-0.0121)*x**3 + (-0.0129)*x**2*y + (0.0475)*x*y**2 + (-0.0227)*y**3
Z_heat = 6.4264 + (0.0890)*x + (-0.0373)*y + (0.1009)*x**2 + (-0.1707)*x*y + (0.0802)*y**2 + (-0.0060)*x**3 + (0.0114)*x**2*y + (-0.0086)*x*y**2 + (0.0032)*y**3

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
