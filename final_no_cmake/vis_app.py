import matplotlib.pyplot as plt # for plots
import pandas as pd

def draw_line(p1,p2,fig,c='k',lw=1.5,ls='-'):
    fig.plot([p1[0],p2[0]], [p1[1],p2[1]], c, linestyle=ls,linewidth=lw)

def draw_point(p,fig,c='k'):
    if(p=="NOT_VISIBLE"):
        return
    fig.plot([p[0]], [p[1]], c+'o',markersize=4)

def draw_points(points,fig,c='k'):
    for point in points:
        draw_point(point,fig,c)

def draw_poly(CH,fig,c='k',lw=1.5,ls='-'):
    n=len(CH)
    for i in range(n):
        draw_line(CH[i],CH[(i+1)%n],fig,c,lw,ls)

def draw_closest_connections(CH,closest_points,fig):
    n=len(CH)
    for i in range(n):
        if closest_points[i]=="NOT_VISIBLE":
            continue        
        draw_line(CH[i],closest_points[i],fig,c='b',ls='--')
        draw_line(closest_points[i],CH[(i+1)%n],fig,c='b',ls='--')

def draw_poly_open(CH,fig,c='k',lw=1.5,ls='-'):
    n=len(CH)
    for i in range(n-1):
        draw_line(CH[i],CH[(i+1)%n],fig,c,lw,ls)

def draw_visibility(visible_points,point,fig):
    n=len(visible_points)
    for i in range(n):      
        draw_line(visible_points[i],point,fig,c='b',ls='--')

def draw_visibility_ch(visible_points,point,fig,c='k'):    
    draw_line(visible_points[0],point,fig,c,ls='--')
    draw_line(visible_points[-1],point,fig,c,ls='--')

def draw_visible_edges_poly(edges_vis,point,fig,c1='r',c2='b'):
    for edge_vis in edges_vis:
        p1,p2=edge_vis[0]
        vis=edge_vis[1]
        draw_line(p1,p2,fig,c1)
        
        if vis=="1":
            draw_line(p1,point,fig,c2,ls='--')
            draw_line(p2,point,fig,c2,ls='--')
        

def points_from_file(path):      
    file1 = open(path, 'r')
    Lines = file1.readlines()

    count = 0
    # Strips the newline character
    points=[]
    for line in Lines:
        try:
            x,y = line.split()
            points+=[[float(x),float(y)]]
        except:
            points+=["NOT_VISIBLE"]

    file1.close()
    
    return points

def edges_vis_from_file(path):
    file1 = open(path, 'r')
    Lines = file1.readlines()

    count = 0
    # Strips the newline character
    edges_vis=[]
    for line in Lines:
        x1,y1,x2,y2,vis = line.split()
        edge=[[float(x1),float(y1)],[float(x2),float(y2)]]
        edges_vis+=[[edge,vis]]

    file1.close()
    
    return edges_vis    

# matplotlib to draw graphs
import matplotlib
import matplotlib.pyplot as plt

# UI stuff
import PySimpleGUI as sg
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# for sin, cos, pi
import math

matplotlib.use("TkAgg")

# used to draw a figure on our UI
def draw_figure(canvas, figure):
    figure_canvas_agg = FigureCanvasTkAgg(figure, canvas)
    figure_canvas_agg.draw()
    figure_canvas_agg.get_tk_widget().pack(side="top", fill="both", expand=1)
    return figure_canvas_agg

# necessary to reset the figure on the UI, without this each draw happens below the previous one
def delete_figure_agg(figure_agg):
    figure_agg.get_tk_widget().forget()

def draw_alg(alg,vis_counter,f,vis_min):
    if alg == 'incremental':
        draw_inc(vis_counter,f,vis_min)
    if alg == 'convex_hull':
        draw_ch(vis_counter,f,vis_min)
    if alg == 'onion':
        return

def draw_min_ch(fig):
    points=points_from_file("visualisation/points")
    draw_points(points,fig)
    
    poly_line=points_from_file("visualisation/poly_line_")
    draw_poly(poly_line,fig)

def draw_ch(vis_counter,fig,vis_min):
    f.clear()
    f.axis("equal")
    
    if(vis_min):
        draw_min_ch(fig);
        return;
    
    steps=get_steps_ch();
    
    points=points_from_file("visualisation/points")
    draw_points(points,fig)
    
    if vis_counter<steps-2:
        closest_points=points_from_file("visualisation/closest_"+str(vis_counter))    
        draw_points(closest_points,fig,c='r')

    if vis_counter>0 and vis_counter<steps-1:
        prev_poly_line=points_from_file("visualisation/poly_line_"+str(vis_counter-1))
        draw_poly(prev_poly_line,fig,c='r')
    
    if vis_counter==steps-1:
        vis_counter-=1
        
    poly_line=points_from_file("visualisation/poly_line_"+str(vis_counter))
    draw_poly(poly_line,fig)
    if vis_counter<steps-2:    
        draw_closest_connections(poly_line,closest_points,fig)

def draw_min_inc(fig):
    points=points_from_file("visualisation/points")
    draw_points(points,fig)
    
    ch=points_from_file("visualisation/ch_")
    draw_poly(ch,fig,ls='--')
    
    poly_line=points_from_file("visualisation/poly_line_")
    draw_poly(poly_line,fig)

def draw_inc(vis_counter,fig,vis_min):
    f.clear()
    f.axis("equal")
    
    if(vis_min):
        draw_min_inc(fig)
        return
    
    steps=get_steps_inc()
    
    points=points_from_file("visualisation/points")
    draw_points(points,fig)
    
    ch=points_from_file("visualisation/ch_"+str(vis_counter))
    draw_poly(ch,fig,ls='--')
    
    poly_line=points_from_file("visualisation/poly_line_"+str(vis_counter))
    draw_poly(poly_line,fig)
    
    if vis_counter<steps-1:
        next_point=points[vis_counter+3]
        draw_point(next_point,fig,c='r')
        
        visible_points=points_from_file("visualisation/visible_"+str(vis_counter))
        draw_visibility_ch(visible_points,next_point,fig)
        
        edges_vis=edges_vis_from_file("visualisation/visible_poly_"+str(vis_counter))
        draw_visible_edges_poly(edges_vis,next_point,fig,c1='r',c2='b')
    
    return

def get_steps_alg(alg):
    if alg == 'incremental':
        return get_steps_inc()
    if alg == 'convex_hull':
        return get_steps_ch()
    if alg == 'onion':
        return get_steps_onion()

def get_steps_inc():
    points=points_from_file("visualisation/points")    
    steps = len(points)-2
    return steps

def get_steps_ch():
    points=points_from_file("visualisation/points")
    poly_line=points_from_file("visualisation/poly_line_0")
    
    steps = len(points) - len(poly_line)
    return steps+2

def get_steps_onion():
    return 1

def handle_alg_event(window,event):
    vals=[]
    if event=='-INC-':
        for i in range(7):
            vals+=[True]
        for i in range(5):
            vals+=[False]
    
    if event=='-CONV-':
        for i in range(3):
            vals+=[True]
        for i in range(9):
            vals+=[False]
            
    if event=='-ONION-':
        for i in range(7):
            vals+=[False]
        for i in range(5):
            vals+=[True]

    for i in range(len(vals)):
        window['-R'+str(i+1)+'-'].update(disabled=not vals[i])
    

def get_val_radio(vals,bools):
    for i in range(len(vals)):
        if bools[i]:
            return vals[i]

import os
import time

# UI stuff below


# left column, the drawing and the sum below
col1 = [
    [sg.Canvas(key="-CANVAS-")],
    [sg.Button("<<"),sg.Button("<"),sg.Text("0",key="-CURRENT-"),sg.Text("/ "+str(0),key="-MAX_STEPS-"), sg.Button(">"),sg.Button(">>")]
]

sub_col2 = [
    [sg.Text("alg:       "),
     sg.Radio('inc', "RAD_ALG", default=True, enable_events=True, key='-INC-'),
     sg.Radio('ch', "RAD_ALG", default=False, enable_events=True, key='-CONV-'),
     sg.Radio('onion', "RAD_ALG", default=False, enable_events=True, key='-ONION-')],
    
    [sg.Text("edge_sel:  "),
     sg.Radio('1', "RAD_EDGE", default=True,key='-R1-'), 
     sg.Radio('2', "RAD_EDGE", default=False,key='-R2-'), 
     sg.Radio('3', "RAD_EDGE", default=False,key='-R3-')],
    
    [sg.Text("inc_init:  "),
     sg.Radio('1a', "RAD_INIT_INC", default=True,key='-R4-'), 
     sg.Radio('1b', "RAD_INIT_INC", default=False,key='-R5-'), 
     sg.Radio('2a', "RAD_INIT_INC", default=False,key='-R6-'), 
     sg.Radio('2b', "RAD_INIT_INC", default=False,key='-R7-')],
    
    [sg.Text("onion_init:"),
     sg.Radio('1', "RAD_INIT_ONION", default=True,key='-R8-'), 
     sg.Radio('2', "RAD_INIT_ONION", default=False,key='-R9-'), 
     sg.Radio('3', "RAD_INIT_ONION", default=False,key='-R10-'), 
     sg.Radio('4', "RAD_INIT_ONION", default=False,key='-R11-'), 
     sg.Radio('5', "RAD_INIT_ONION", default=False,key='-R12-')],
    [sg.Text("vis:       "),
     sg.Radio('0', "RAD_VIS",key='-R13-', default=True), 
     sg.Radio('1', "RAD_VIS",key='-R14-', default=False), 
     sg.Radio('2', "RAD_VIS",key='-R15-', default=False)],
    
]
col2 = [
    [sg.Text("Input file:  ")],
    [sg.Input(key="-INPUT_FILE-",size=(35),change_submits=True)],
    [sg.FileBrowse(key="-BROWSE-",initial_folder = os.getcwd(), enable_events=True)],
    [sg.Text("")],
    
    [sg.Text("Output file: ")],
    [sg.Input("data.out",key="-OUTPUT_FILE-",size=(35))],
    [sg.Text("")],
    
    [sg.Column(sub_col2,element_justification="middle")],
    [sg.Text("")],
    [sg.Text("              "),sg.Button("Run",font="Helvetica 18")]
]

# create the layout, col1, seperator, col2
layout = [
    [
        sg.Column(col1,element_justification="center"),
        sg.VSeperator(),
        sg.Column(col2,element_justification="left"),
    ]
]

# Create the window 
window = sg.Window(
    "Visualisation App",
    layout,
    return_keyboard_events=True,
    relative_location=(-300,-300),
    finalize=True,
    keep_on_top=True,
    element_justification="center",
    font="Courier 10",
)

# create the matplotlib figure for drawing
fig = matplotlib.figure.Figure(figsize=(8, 8), dpi=100)
f = fig.add_subplot(111)

# Draw the plot and add the figure to the window
figure_agg=draw_figure(window["-CANVAS-"].TKCanvas, fig)

# block onion buttons 
handle_alg_event(window,'-INC-')

# set stuff
vis='0'
vis_counter=0
steps=1
alg='incremental'

# widnow event loop
while True:
    # get events and values
    event, values = window.read()

    # close if X is pressed
    if event == sg.WIN_CLOSED:
        break

    # delete previous canvas of the ui
    delete_figure_agg(figure_agg)

    # update input file after browse
    if(event=='-BROWSE-'):
        window['-INPUT_FILE-'].update(values['-BROWSE-'])
    
    # enable or disable buttons based on chosen algorithm
    handle_alg_event(window,event)    
    
    # on run call to_polygon
    if event=='Run':
        
        # create call
        call = "./to_polygon -i " + values['-INPUT_FILE-'] + " -o " + values['-OUTPUT_FILE-']
        
        alg = get_val_radio(['incremental','convex_hull','onion'],[values['-INC-'],values['-CONV-'],values['-ONION-']])
        edge = get_val_radio(['1','2','3'],[values['-R1-'],values['-R2-'],values['-R3-']])
        init_inc = get_val_radio(['1a','1b','2a','2b'],[values['-R4-'],values['-R5-'],values['-R6-'],values['-R7-']])
        onion_init = get_val_radio(['1','2','3','4','5'],[values['-R8-'],values['-R9-'],values['-R10-'],values['-R11-'],values['-R12-']])
        vis = get_val_radio(['0','1','2'],[values['-R13-'],values['-R14-'],values['-R15-']])
        
        call += " -algorithm " + alg
        
        if alg == 'incremental':
            call += " -edge_selection "+edge
            call += " -initialization "+init_inc
        if alg == 'convex_hull':
            call += " -edge_selection "+edge
        if alg == 'onion':
            call += " -onion_initialization "+onion_init
    
        if vis!='0':
            call += " -vis "+vis
        
        #remove previous visualisation
        vis_counter=0
        vis_counter
        
        # make call
        stream = os.popen(call)
        output = stream.read()
	
        #print(output)

    # if < is pressed    
    if event == '<' or event=="Left:37":
        # decrease vis_counter, draw with new vis_counter
        vis_counter=(vis_counter-1)%steps
    if event == '>' or event == "Right:39":
        # increase vis_counter, draw with new vis_counter
        vis_counter=(vis_counter+1)%steps
    if event == '<<' or event == "Down:40":
        # decrease vis_counter, draw with new vis_counter
        vis_counter=max(vis_counter-10,0)%steps
    if event == '>>' or event == "Up:38":
        # increase vis_counter, draw with new vis_counter
        vis_counter=min(vis_counter+10,steps-1)%steps  
        
    if os.path.exists('visualisation') and (vis=='1' or vis=='2'):
        if vis=='1':
            steps=get_steps_alg(alg)
            window['-MAX_STEPS-'].update("/ "+str(steps-1))
        vis_min = vis=='2'
        if vis=='2':
            vis_counter=0
            window['-MAX_STEPS-'].update("/ "+str(0))
        draw_alg(alg,vis_counter,f,vis_min)
    figure_agg = draw_figure(window['-CANVAS-'].TKCanvas, fig)
    # update "page" number
    window['-CURRENT-'].update(str(vis_counter))
        
window.close()





