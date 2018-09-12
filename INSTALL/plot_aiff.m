clear all;
close all;
% Frame by frame AIFF file plotter, and FFT plotter
%----------------------------%

fileName = '/home/djelgroucho/Desktop/demo/aiff/100/sine/48kHz100_20180909T041755474707Z.aiff';

plot = 'freq'; %'time', 'freq', 'dropoff'

T = 500; % samples per frame
N0 = 1; % initial frame
wait = 1; % delay in seconds

%----------------------------%
[file, fs] = audioread(fileName);
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
  rec_f = fftshift(fft(recording));
  f = fs*(-length(rec_f)/2:(length(rec_f)/2 -1))/length(rec_f);
  rec_abs = abs(rec_f);
  rec_abs = rec_abs/max(rec_abs);
  stem(f, rec_abs);
  xlabel('Frequency (Hz)');
  ylabel('Normalised Magnitude');
  title(['Spectral Domain: Fs = ', num2str(fs), ' Hz']);
end
