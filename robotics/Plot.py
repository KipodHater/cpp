import numpy as np
import plotly.graph_objects as go

X = np.linspace(-2, 2, 100)
Y = np.linspace(0, 8, 100)
y, x = np.meshgrid(Y, X)

Z_height =   90.0354 + (-10.9830)*x + (8.9389)*y + (0.3821)*x**2 + (-0.3219)*x*y + (0.0457)*y**2 + (0.0803)*x**3 + (-0.1251)*x**2*y + (0.1805)*x*y**2 + (-0.0700)*y**3 + (-0.0063)*x**4 + (0.0088)*x**3*y + (-0.0187)*x**2*y**2 + (0.0140)*x*y**3 + (-0.0043)*y**4
Z_heat = 6.4731 + (-0.1214)*x + (0.0216)*y + (0.2003)*x**2 + (-0.2279)*x*y + (0.0857)*y**2 + (-0.0219)*x**3 + (0.0247)*x**2*y + (-0.0129)*x*y**2 + (0.0036)*y**3 + (0.0009)*x**4 + (-0.0010)*x**3*y + (0.0005)*x**2*y**2 + (-0.0002)*x*y**3 + (0.0001)*y**4

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
