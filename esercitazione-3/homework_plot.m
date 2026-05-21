% homework_plot.m
% Reads am_phasor.csv and plots:
%   1. The modulus |x_n| as a function of time
%   2. The trajectory of x_n on the complex plane
%
% Expected CSV format (no header row):
%   real part, imaginary part, modulus
%
% Usage: run this script from the folder containing the CSV file
%        >> plot_am_phasor

clear; clc; close all;

%% Configuration
filename = 'am_phasor.csv';
Fs       = 1000.0;  % Sampling frequency [Hz]
out_pdf  = 'homework_plot.pdf';
out1_svg  = 'homework_1_plot.svg';
out2_svg  = 'homework_2_plot.svg';

if isfile(out_pdf), delete(out_pdf); end
if isfile(out1_svg), delete(out1_svg); end
if isfile(out2_svg), delete(out2_svg); end
%% Load data
if ~isfile(filename)
    error('File "%s" not found. Make sure the C program has been run first.', filename);
end

data = readmatrix(filename);
re   = data(:, 1);
im   = data(:, 2);
mag  = data(:, 3);
N    = length(re);
t    = (0:N-1) / Fs;  % Time axis [s]

%% Plot 1 - Modulus vs time
fig1 = figure('Name', 'AM Phasor - Modulus', 'NumberTitle', 'off');

plot(t, mag, 'Color', [0.2 0.4 0.8], 'LineWidth', 1.2);
xlabel('Tempo [s]');
ylabel('|x_n|', 'Interpreter', 'tex');
title('Modulo del fasore AM in funzione del tempo');
grid on;
xlim([t(1) t(end)]);

% Remove toolbars
ax = gca;
ax.Toolbar.Visible = 'off';
exportgraphics(fig1, out_pdf, 'Resolution', 300);
exportgraphics(fig1, out1_svg, 'Resolution', 300);

%% Plot 2 - Trajectory on the complex plane
fig2 = figure('Name', 'AM Phasor - Complex Plane', 'NumberTitle', 'off');
colormap('jet');
cmap = colormap;
hold on;

M   = 50; % number of segments for color gradient
seg = floor(N / M);
for k = 1:M
    idx   = (k-1)*seg+1 : min(k*seg+1, N);
    color = cmap(floor((k-1)*(size(cmap,1)-1)/(M-1))+1, :);
    plot(re(idx), im(idx), 'Color', color, 'LineWidth', 0.8);
end

colorbar;
xlabel('Re\{x_n\}', 'Interpreter', 'tex');
ylabel('Im\{x_n\}', 'Interpreter', 'tex');
title('Traiettoria del fasore AM sul piano complesso');
grid on;
axis equal;
box on;

% Remove toolbars
ax = gca;
ax.Toolbar.Visible = 'off';
exportgraphics(fig2, out_pdf, 'Resolution', 300, 'Append', true);
exportgraphics(fig2, out2_svg, 'Resolution', 300);