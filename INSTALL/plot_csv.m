clear all;
close all;
% Frame by frame CSV file plotter
%----------------------------%

file = csvread('/home/djelgroucho/Desktop/85kHz_20180908T234510432820Z.csv');
plot = 'freq'; %'time', 'freq', 'dropoff'
T = 500; % samples per frame
N0 = 1; % initial frame
wait = 1; % delay in seconds
fs = 200000;
%----------------------------%

h = 2; % header skip
start = h + 1;
stop = length(file);

if strcmp(plot, 'time')
  N = floor(length(file) / T); % max allowable frames
  if N0 < 1 || N0 > N
    break;
  end
  for i = N0:N
    t0 = T * (i - 1) + N0 + 1;
    t =  t0 + T;
    ti = t0:t;
    scatter(ti, file(ti, 2), '.');
    line(ti, file(ti, 2));
    title(['Frame ', num2str(i), ' / ', num2str(N)]);
    ylim([-10, 10]);
    xlim([-inf, t]);
    xlabel('sample');
    ylabel('V');
    pause(wait);
  end
elseif strcmp(plot,'dropoff')
  thres = 5.1; % 5V + 2%
  diff = file(start:stop, 2).*(abs(file(start:stop, 2)) > 5.1);
  indices = find(diff > 0);
  scatter(file(indices, 1), diff(indices)); 
  grid on;
  title('Dropoffs');
  xlabel('sample');
  ylabel('V');
elseif strcmp(plot, 'freq')
  recording = file(start:stop, 2);
  r_fft = fftshift(fft(recording));
  f_r = fs*(-length(r_fft)/2:(length(r_fft)/2 -1))/length(r_fft);
  r_fft_mag = abs(r_fft);
  r_fft_mag_norm = r_fft_mag/max(r_fft_mag);
  stem(f_r, r_fft_mag_norm);
  xlabel('Frequency (Hz)');
  ylabel('Normalised Magnitude');
  title(['Spectral Domain: Fs = ', num2str(fs), ' Hz']);
end
