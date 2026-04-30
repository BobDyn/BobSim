import pandas as pd
from dash import Dash, dcc, html, Input, Output
import plotly.express as px

df = pd.read_csv("sine_test.csv")

app = Dash(__name__)

app.layout = html.Div([
    html.H3("Parametric Plot Explorer"),

    dcc.Dropdown(df.columns, value=df.columns[0], id='x'),
    dcc.Dropdown(df.columns, value=df.columns[1], id='y'),

    dcc.Graph(id='plot')
])

@app.callback(
    Output('plot', 'figure'),
    Input('x', 'value'),
    Input('y', 'value')
)
def update(x, y):
    return px.line(df, x=x, y=y)

app.run(debug=True)