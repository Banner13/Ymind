import sys

from PySide6.QtWebEngineWidgets import QWebEngineView
from BokehHtml import CreateHtml

datattt = {
    'time': [1, 2, 3, 4, 5],
    'y1': [6, 7, 2, 4, 5],
    'y2': [1, 2, 4, 8, 6],
    'y3': [3, 5, 6, 7, 2],
    'y4': [60, 70, 20, 40, 50],
    'y5': [10, 20, 40, 80, 60],
    'y6': [30, 50, 60, 70, 20],
    'y7': [60, 70, 20, 40, 50],
    'y8': [11, 12, 14, 18, 16],
    'y9': [13, 15, 16, 17, 12],
    'y10': [16, 17, 12, 14, 15],
    'y11': [11, 12, 14, 18, 16],
    'y12': [23, 25, 26, 27, 22]
}



class BokehWebEngineView(QWebEngineView):
    def __init__(self, data=None, parent=None):
        super().__init__(parent)

        self.df = data
        # self.df = datattt
        self.html = CreateHtml(datattt)

        self.setHtml(self.html)
        self.setMinimumSize(300, 200)

"""
    def resizeEvent(self, event):
        super().resizeEvent(event)
        #self.html = self.df.plot_bokeh(kind="line", width=self.width()-50, height=self.height()-50, return_html=True, show_figure=False)
        self.setHtml(self.html_with_js)
"""

