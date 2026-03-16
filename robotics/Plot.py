import numpy as np
import plotly.graph_objects as go

X = np.linspace(-2, 2, 100)
Y = np.linspace(0, 5.3, 100)
y, x = np.meshgrid(X, Y)

Z_height =   88.0974 + (-14.4672)*x + (10.4733)*y + (2.6164)*x**2 + (-0.1367)*x*y + (-0.7472)*y**2 + (-0.1973)*x**3 + (-0.0947)*x**2*y + (0.4193)*x*y**2 + (-0.3971)*y*83
Z_heat =   5.7661 + (0.7385)*x + (-0.2812)*y + (0.0389)*x**2 + (-0.0293)*x*y + (-0.0169)*y**2 + (-0.0063)*x**3 + (-0.0026)*x**2*y + (0.0305)*x*y**2 + (-0.0243)*y**3
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
