"""Shared style and export routine for the manuscript figures.

Every manuscript-figure cell in the ResultAnalysis notebooks imports this module, so all
figures share one palette, one font, one set of sizes and one export routine.

Following common journal figure specifications:
- Width 89 mm (single column) or 183 mm (double column); height at most 170 mm.
- Arial/Helvetica, text 5-7 pt; editable (not outlined) text in vector files; RGB colour;
  raster images at least 300 dpi.
- Colour-blind-accessible palette (Okabe-Ito / Wong 2011), no red/green pairs; no
  background gridlines; axes labelled "Quantity (unit)".

Our own choices, not taken from the specifications:
- No titles inside the plot area; panel letters are added later in the layout tool.
- 0.5 pt axes; simulator results drawn as points (one marker shape per tool), references
  as a continuous dashed line (analytical) or open circles (experimental).
- Each tool keeps one colour across all figures and also gets its own marker as a second
  cue (PhysiCell/TiSim are only 7.6 dE apart under deuteranopia).
- The plotted series of every figure are written to a source-data CSV next to it, in case
  the journal asks for Source Data at acceptance.

Usage in a notebook::

    import figure_style as ns
    with ns.style():
        fig, ax = plt.subplots(figsize=ns.size(ns.SINGLE_COL_MM, 60))
        for tool in ns.TOOL_ORDER:
            ax.plot(t, y, **ns.tool_series(tool))
        ax.plot(t_ref, y_ref, **ns.ANALYTICAL)
        ns.style_axes(ax)
        ns.export(fig, 'diffusion_decay', 'decay_concentration_error', root=ROOT)
"""
from __future__ import annotations

import os
import re
from pathlib import Path

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

MM = 1 / 25.4  # inches per millimetre
SINGLE_COL_MM = 89
DOUBLE_COL_MM = 183
MAX_HEIGHT_MM = 170
DPI = 300

TOOL_ORDER = ['BioDynaMo', 'Chaste', 'CompuTiX', 'PhysiCell', 'TiSim']

# Okabe-Ito; validated with the dataviz palette checker (all checks pass, CVD floor band
# for PhysiCell/TiSim, hence the markers below).
TOOL_COLORS = {
    'BioDynaMo': '#E69F00',  # orange
    'Chaste': '#0072B2',     # blue
    'CompuTiX': '#D55E00',   # vermillion
    'PhysiCell': '#009E73',  # bluish green
    'TiSim': '#CC79A7',      # reddish purple
}
TOOL_MARKERS = {
    'BioDynaMo': 'o',
    'Chaste': 's',
    'CompuTiX': '^',
    'PhysiCell': 'D',
    'TiSim': 'v',
}
REFERENCE_COLOR = '#000000'

# Simulator series: 'line' (line + sparse markers), 'scatter' (points only) or 'points_line'
# (points over a faint alpha-0.5 line, to follow each tool between points).
# References stay continuous: the analytical solution is a dashed line, experiment open circles.
SERIES_STYLE = 'line'
MARKER_SPACING = 0.025
LINE_ALPHA = 0.5  # line opacity in 'points_line'  # fraction of the axes diagonal between displayed markers

# One look for every reference series, in every figure.
ANALYTICAL = dict(color=REFERENCE_COLOR, linestyle=(0, (4, 2)), linewidth=1.0,
                  label='Analytical', zorder=3)
EXPERIMENTAL = dict(color=REFERENCE_COLOR, linestyle='none', marker='o', markersize=3.5,
                    markerfacecolor='white', markeredgecolor=REFERENCE_COLOR,
                    markeredgewidth=0.8, label='Experimental', zorder=4)

FONT_FAMILY = ['Arial', 'Helvetica', 'Liberation Sans', 'Nimbus Sans', 'DejaVu Sans']
SVG_FONT_FAMILY = 'Arial, Helvetica, sans-serif'

RC = {
    'font.family': 'sans-serif',
    'font.sans-serif': FONT_FAMILY,
    'font.size': 7,
    'axes.labelsize': 7,
    'axes.titlesize': 7,
    'xtick.labelsize': 6,
    'ytick.labelsize': 6,
    'legend.fontsize': 6,
    'legend.title_fontsize': 6,
    'legend.frameon': False,
    'legend.handlelength': 2.2,
    'legend.handletextpad': 0.5,
    'legend.columnspacing': 1.2,
    'legend.borderaxespad': 0.3,
    'lines.linewidth': 1.0,
    'lines.markersize': 3,
    'axes.linewidth': 0.5,
    'axes.edgecolor': '#000000',
    'axes.labelcolor': '#000000',
    'axes.labelpad': 3,
    'axes.spines.top': False,
    'axes.spines.right': False,
    'axes.grid': False,
    'axes.unicode_minus': True,
    'xtick.color': '#000000',
    'ytick.color': '#000000',
    'xtick.direction': 'out',
    'ytick.direction': 'out',
    'xtick.major.width': 0.5,
    'ytick.major.width': 0.5,
    'xtick.major.size': 2.5,
    'ytick.major.size': 2.5,
    'xtick.major.pad': 2,
    'ytick.major.pad': 2,
    'mathtext.default': 'regular',
    'figure.dpi': 150,
    'savefig.dpi': DPI,
    'savefig.facecolor': 'white',
    'svg.fonttype': 'none',   # keep text as editable <text> for Figma
    'pdf.fonttype': 42,
    'ps.fonttype': 42,
}


def find_repo_root(start: Path | None = None) -> Path:
    """Return the first folder, from ``start`` (default: CWD) upwards, that holds ResultAnalysis/figure_style.py."""
    start = (Path.cwd() if start is None else Path(start)).resolve()
    for parent in (start, *start.parents):
        if (parent / 'ResultAnalysis' / 'figure_style.py').is_file():
            return parent
    raise FileNotFoundError(f'Run from inside the observatory_benchmark repository (no ResultAnalysis/figure_style.py above {start})')


def figures_dir(root: Path) -> Path:
    """Figure export folder: $FIGURES_DIR if set, else <repository>/figures."""
    return Path(os.environ.get('FIGURES_DIR', Path(root).resolve() /'ResultAnalysis'/ 'figures'))


def apply_style() -> None:
    """Install the shared rcParams for the rest of the notebook."""
    mpl.rcParams.update(RC)


def style():
    """Context manager with the shared rcParams; leaves other (supplementary) cells untouched."""
    return mpl.rc_context(RC)


def size(width_mm: float, height_mm: float) -> tuple[float, float]:
    """Figure size in inches from millimetres."""
    if height_mm > MAX_HEIGHT_MM:
        raise ValueError(f'height {height_mm} mm exceeds the {MAX_HEIGHT_MM} mm page limit')
    return width_mm * MM, height_mm * MM


def tool_series(tool: str, kind: str | None = None, **overrides) -> dict:
    """``ax.plot`` kwargs for a simulator series: fixed colour and marker per tool.

    ``kind='scatter'`` draws markers only, no connecting line.
    Dense series (up to 7000 native samples) would merge into a solid band, so markers are
    thinned for display to about one per MARKER_SPACING of the axes diagonal, measured
    along the curve, and staggered per tool so coinciding tools interleave instead of
    hiding each other. Sparse series (fewer samples than that) show every sample. The
    source-data CSV still holds every native sample. ``kind='points_line'`` adds a
    faint (alpha 0.5) line under the points; ``kind='line'`` gives line + sparse markers.
    """
    kind = kind or SERIES_STYLE
    color = TOOL_COLORS[tool]
    stagger = MARKER_SPACING * TOOL_ORDER.index(tool) / len(TOOL_ORDER)
    kwargs = dict(color=color, label=tool, zorder=2, marker=TOOL_MARKERS[tool],
                  markerfacecolor=color, markeredgecolor='white', markeredgewidth=0.3,
                  markevery=(stagger, MARKER_SPACING))
    if kind == 'scatter':
        kwargs.update(linestyle='none', markersize=3.2)
    elif kind == 'points_line':
        # Faint line via an RGBA colour, so the markers stay opaque and the legend shows both.
        kwargs.update(color=mpl.colors.to_rgba(color, LINE_ALPHA), linewidth=0.8,
                      markersize=3.2)
    elif kind == 'line':
        kwargs.update(linewidth=1.0, markersize=3, markevery=(stagger, 0.1))
    else:
        raise ValueError(f"kind must be 'scatter', 'points_line' or 'line', not {kind!r}")
    kwargs.update(overrides)
    return kwargs


def style_axes(ax) -> None:
    """Per-axis cleanup that rcParams cannot express."""
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.grid(False)
    ax.tick_params(which='both', direction='out')
    ax.set_title('')


def ordered_legend(ax_or_fig, handles, labels, **kwargs):
    """Legend with simulators in TOOL_ORDER first, then reference series."""
    pairs = dict(zip(labels, handles))
    order = [t for t in TOOL_ORDER if t in pairs] + [l for l in pairs if l not in TOOL_ORDER]
    return ax_or_fig.legend([pairs[l] for l in order], order, **kwargs)


def _source_data(fig) -> pd.DataFrame:
    """Long-form table of every labelled line/marker series in the figure."""
    rows = []
    for panel, ax in enumerate(fig.get_axes()):
        for line in ax.get_lines():
            label = line.get_label()
            if label.startswith('_'):
                continue
            x, y = (np.asarray(v, dtype=float) for v in line.get_data())
            rows.append(pd.DataFrame({
                'panel': panel + 1,
                'x_label': ax.get_xlabel(),
                'y_label': ax.get_ylabel(),
                'series': label,
                'x': x,
                'y': y,
            }))
    return pd.concat(rows, ignore_index=True) if rows else pd.DataFrame()


def _fix_svg_fonts(svg_path: Path) -> None:
    """Point every text element at Arial/Helvetica, whatever font rendered locally."""
    text = svg_path.read_text(encoding='utf-8')
    text = re.sub(r'font-family:[^;"]*', f'font-family: {SVG_FONT_FAMILY}', text)
    text = re.sub(r'font-family="[^"]*"', f'font-family="{SVG_FONT_FAMILY}"', text)
    svg_path.write_text(text, encoding='utf-8')


def _save_png_rgb(fig, path: Path, **save_kw) -> None:
    """300 dpi PNG flattened onto white, RGB (no alpha channel), as journal figure specifications recommend."""
    from PIL import Image

    fig.savefig(path, format='png', dpi=DPI, **save_kw)
    with Image.open(path) as image:
        rgba = image.convert('RGBA')
    flat = Image.new('RGB', rgba.size, (255, 255, 255))
    flat.paste(rgba, mask=rgba.split()[-1])
    flat.save(path, dpi=(DPI, DPI))


def export(fig, scenario: str, stem: str, root: Path, also: Path | None = None,
           also_stem: str | None = None) -> dict:
    """Save ``fig`` as 300 dpi PNG + editable SVG + source-data CSV.

    Files go to <figures_dir>/<scenario>/{png,svg,source_data}/<stem>.*; ``also`` (a folder in
    the repository, e.g. ResultAnalysis/plots/...) receives a PNG and SVG copy as well, named
    ``also_stem`` (default: ``stem``). Call inside ``with style():`` so svg.fonttype applies.
    """
    also_stem = also_stem or stem
    out = figures_dir(root) / scenario
    paths = {
        'png': out / 'png' / f'{stem}.png',
        'svg': out / 'svg' / f'{stem}.svg',
        'source_data': out / 'source_data' / f'{stem}.csv',
    }
    for p in paths.values():
        p.parent.mkdir(parents=True, exist_ok=True)
    save_kw = dict(bbox_inches='tight', pad_inches=0.02, facecolor='white')
    _save_png_rgb(fig, paths['png'], **save_kw)
    fig.savefig(paths['svg'], format='svg', **save_kw)
    _fix_svg_fonts(paths['svg'])
    _source_data(fig).to_csv(paths['source_data'], index=False)
    if also is not None:
        also = Path(also)
        also.mkdir(parents=True, exist_ok=True)
        _save_png_rgb(fig, also / f'{also_stem}.png', **save_kw)
        fig.savefig(also / f'{also_stem}.svg', format='svg', **save_kw)
        _fix_svg_fonts(also / f'{also_stem}.svg')
    for kind, p in paths.items():
        print(f'Saved {kind}: {p}')
    return paths


def concentration_error_figure(selected: pd.DataFrame, analytical: pd.DataFrame, *,
                               value_column: str, analytical_column: str,
                               xlim: float | None, kind: str | None = None):
    """Three stacked panels shared by the decay and uptake benchmarks.

    ``selected`` holds one native-sample series per tool with columns time_min,
    ``value_column``, absolute_error_uM and relative_error_percent. No resampling.
    """
    fig, axes = plt.subplots(3, 1, figsize=size(SINGLE_COL_MM, 115), sharex=True,
                             gridspec_kw={'height_ratios': [1.25, 1, 1]})
    panels = [
        (value_column, 'Average concentration (µM)'),
        ('absolute_error_uM', 'Absolute error (µM)'),
        ('relative_error_percent', 'Relative error (%)'),
    ]
    for axis, (column, ylabel) in zip(axes, panels):
        for tool in TOOL_ORDER:
            group = selected.loc[selected['tool'] == tool].sort_values('time_min')
            if group.empty:
                continue
            axis.plot(group['time_min'], group[column], **tool_series(tool, kind))
        if column == value_column:
            axis.plot(analytical['time_min'], analytical[analytical_column], **ANALYTICAL)
        axis.set_ylabel(ylabel)
        if column != value_column:
            axis.set_ylim(bottom=0)
        style_axes(axis)
    axes[-1].set_xlabel('Time (min)')
    if xlim is not None:
        axes[-1].set_xlim(0, xlim)
    else:
        axes[-1].set_xlim(left=0)
    fig.align_ylabels(axes)
    handles, labels = axes[0].get_legend_handles_labels()
    ordered_legend(fig, handles, labels, loc='lower center', ncol=3,
                   bbox_to_anchor=(0.55, 1.0), handlelength=2.0, columnspacing=1.2)
    fig.tight_layout(pad=0.3, h_pad=0.6)
    return fig, axes
