
from bokeh.resources import CDN
from bokeh.palettes import Category10
from bokeh.embed import file_html
from bokeh.plotting import figure
from bokeh.models import HoverTool, ColumnDataSource, CrosshairTool, Span

TimeStampLab = 'time'

# html兼容Qt附加代码
bokeh_compatable_code = """
if (!String.prototype.replaceAll) {
    String.prototype.replaceAll = function(search, replacement) {
        var target = this;
        return target.replace(new RegExp(search, 'g'), replacement);
    };
}
"""

# 线型图调色板
html_colors = Category10[10]

def CreateHtml(data) -> None :
    if TimeStampLab not in data:
        print("data not found time stamp.\n")
        exit()

    p = figure(title="Example", sizing_mode="stretch_both")

    color_index = 0
    tooltips = []
    for name in data.keys():
        if name != TimeStampLab:  # 忽略 'x' 列
            color = html_colors[color_index % len(html_colors)]
            line = p.line(TimeStampLab, name, source=data, legend_label=f"{name}", line_width=2, color=color, muted_color=color, muted_alpha=0.2)
            hover = HoverTool(
                renderers=[line], 
                # mode='vline',
                tooltips=[(TimeStampLab, f"@{TimeStampLab}"), (name, f"@{name}")],
                attachment="right",
                point_policy="snap_to_data",
                line_policy="nearest"
            )
            tooltips.append(hover)
            color_index += 1

    p.add_tools(*tooltips)

    width = Span(dimension="width", line_dash="dashed", line_width=2)
    height = Span(dimension="height", line_dash="dotted", line_width=2)
    p.add_tools(CrosshairTool(overlay=[width, height]))

    p.legend.location = "right"
    p.legend.click_policy = "hide"  #mute

    html = file_html(p, CDN, "Multiple Lines Example")
    html_with_js = html.replace('</body>', f'\n<script>{bokeh_compatable_code}</script>\n')

    return html_with_js
