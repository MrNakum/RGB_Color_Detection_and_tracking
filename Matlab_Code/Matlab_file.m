close all;

% serial port closing
%fclose(ARDUINO);

%closing webcam object
%delete(vidObj);

%Initialise webcam
vidObj = webcam;

%Initialise some variables
slash = ',';

%SERIAL COMUNICATION%
ARDUINO =serial('COM9','BAUD',2000000); %PORT : ARDUINO COMMUNICATION PORT

%Turn on the serial port
fopen(ARDUINO);

%webcam property 
frame = snapshot(vidObj);
frameSize = size(frame);

for i=1:1000    %set count depend on time

    % Get the snapshot of the current frame
    IMRED = snapshot(vidObj);

    % from the grayscale image to extract the red components in the image.
    diff_im = imsubtract(IMRED(:,:,1), rgb2gray(IMRED));
    
    % Global image threshold using Otsu's method
    gr=graythresh(diff_im);

    %Use a median filter to filter out noise
    diff_im = medfilt2(diff_im, [3 3]);    

    % Convert the resulting grayscale image into a binary image.
    diff_im = im2bw(diff_im,.18);

    % Remove all those pixels less than 300px
    diff_im = bwareaopen(diff_im,300);

    % Label all the connected components in the image.
    [bw bw1] = bwlabel(diff_im, 8);

    % Here we do the image blob analysis.
    % We get a set of properties for each labeled region.
    stats = regionprops(bw, 'BoundingBox', 'Centroid');

    % Display the image
    imshow( IMRED )

    hold on
    
    %This is a loop to bound the red objects in a rectangular box.
    for object = 1:length(stats)
        bb = stats(object).BoundingBox;
        bc = stats(object).Centroid;
        rectangle('Position',bb,'EdgeColor','r','LineWidth',2)
        plot(bc(1),bc(2), '-m+')
        a=text(bc(1)+15,bc(2), strcat('X: ', num2str(round(bc(1))), '    Y: ', num2str(round(bc(2)))));
        set(a, 'FontName', 'Arial', 'FontWeight', 'bold', 'FontSize', 12, 'Color', 'yellow');
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %%%%%%%writing data to arduino%%%%%%%%%
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        % Convert numbers to character array
        Xcord = num2str(round(bc(1)));
        Ycord = num2str(round(bc(2)));
        
        % Concatenate strings
        Cord = strcat(Xcord, slash , Ycord);
        
        % Write data into arduino
        fprintf(ARDUINO , '%s' , char(Cord));
        
        % Print data on screen
        disp(char(Cord));
        
        % Wait for some time 
        pause(0.8);
         
    end
    
    hold off
    end
%closing webcam object   
delete(vidObj);

% serial port closing
fclose(ARDUINO);

clear all

sprintf('%s','Thanks you')

