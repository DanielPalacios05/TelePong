# import sys module 
import pygame 
  
# pygame.init() will initialize all 
# imported module
def receiveInfo(): 
    pygame.init() 
    
    clock = pygame.time.Clock() 

    BLACK = (0, 0, 0)
    WHITE = (255, 255, 255)
    GREEN = (0, 255, 0)
    GRAY = (156, 156, 156)
    
    # it will display on screen 
    screen = pygame.display.set_mode([900, 600]) 
    

    font20 = pygame.font.Font('fonts/256_bytes.ttf', 90)
    font21 = pygame.font.Font('fonts/256_bytes.ttf', 50)
    font22 = pygame.font.Font('fonts/256_bytes.ttf', 30)
    font23 = pygame.font.Font('fonts/256_bytes.ttf', 24)
    font24 = pygame.font.Font('fonts/256_bytes.ttf', 27)

    nickname = '' 
    ipAddress = '' 
    port = '' 

    text1 = font20.render("Bienvenido a TelePong", True, WHITE)
    text2 = font21.render("Ingrese los siguientes campos", True, WHITE)


    text_rect1 = text1.get_rect()
    text_rect2 = text2.get_rect()

    text_rect1.center = (900 // 2, 120)

    # Posicionar el segundo mensaje debajo del primero
    text_rect2.center = (900 // 2, 260)

    
    # create rectangle 
    text3 = font23.render("Nickname", True, WHITE)
    text4 = font23.render("IP Servidor", True, WHITE)
    text5 = font23.render("Puerto Servidor", True, WHITE)

    text6 = font24.render("Iniciar juego", True, BLACK)

    text_rect3 = pygame.Rect(133, 360, 160, 46)
    text_rect4  = pygame.Rect(395, 360, 160, 46)
    text_rect5  = pygame.Rect(630, 360, 160, 46)

    exit_rect  = pygame.Rect(370, 500, 160, 46)

    input_rect = pygame.Rect(100, 400, 160, 46)
    input_rect2 = pygame.Rect(370, 400, 160, 46)
    input_rect3 = pygame.Rect(630, 400, 160, 46)
    
    # color_active stores color(lightskyblue3) which 
    # gets active when input box is clicked by user 
    color_active = WHITE
    
    # color_passive store color(chartreuse4) which is 
    # color of input box. 
    color_passive = GRAY 
    color = color_passive 
    
    active = False
    active2 = False
    active3 = False

    exit = False
    
    while exit == False: 
        screen.fill(BLACK)
        for event in pygame.event.get(): 
    
        # if user types QUIT then the screen will close 
            if event.type == pygame.MOUSEBUTTONDOWN:
                if exit_rect.collidepoint(event.pos): 
                    pygame.quit() 
                    exit = True
                    
    
            if event.type == pygame.MOUSEBUTTONDOWN: 
                if input_rect.collidepoint(event.pos): 
                    active = True
                else:
                    active = False
                
                if input_rect2.collidepoint(event.pos):
                    active2 = True
                else: 
                    active2 = False
                
                if input_rect3.collidepoint(event.pos):
                    active3 = True
                else: 
                    active3 = False

            if active:
                if event.type == pygame.KEYDOWN: 

                # Check for backspace 
                    if event.key == pygame.K_BACKSPACE: 
                        # get text input from 0 to -1 i.e. end. 
                        nickname = nickname[:-1] 
        
                    # Unicode standard is used for string 
                    # formation 
                    else: 
                        nickname += event.unicode
            if active2:
                if event.type == pygame.KEYDOWN: 
                # Check for backspace 
                    if event.key == pygame.K_BACKSPACE: 
                        # get text input from 0 to -1 i.e. end. 
                        ipAddress = ipAddress[:-1] 

                    # Unicode standard is used for string 
                    # formation 
                    else: 
                        ipAddress += event.unicode
            
            if active3:
                if event.type == pygame.KEYDOWN: 
                # Check for backspace 
                    if event.key == pygame.K_BACKSPACE: 
                        # get text input from 0 to -1 i.e. end. 
                        port = port[:-1] 

                    # Unicode standard is used for string 
                    # formation 
                    else: 
                        port += event.unicode
    # it will set background color of screen 
        
        if exit == False:
            if active: 
                color1 = color_active 
            else: 
                color1 = color_passive

            if active2: 
                color2 = color_active 
            else: 
                color2 = color_passive
            
            if active3: 
                color3 = color_active 
            else: 
                color3 = color_passive 
                
            # draw rectangle and argument passed which should 
            # be on screen 
            pygame.draw.rect(screen, color1, input_rect, 2, 3) 
            pygame.draw.rect(screen, color2, input_rect2, 2, 3)
            pygame.draw.rect(screen, color3, input_rect3, 2, 3)
            pygame.draw.rect(screen, WHITE, exit_rect)
        
            text_surface = font22.render(nickname, True, (255, 255, 255)) 

            text_surface2 = font22.render(ipAddress, True, (255, 255, 255)) 

            text_surface3 = font22.render(port, True, (255, 255, 255)) 

            screen.blit(text1, text_rect1)
            screen.blit(text2, text_rect2)
            screen.blit(text3, text_rect3)
            screen.blit(text4, text_rect4)
            screen.blit(text5, text_rect5)
            screen.blit(text6, (exit_rect.x+10, exit_rect.y+6))
            
            # render at position stated in arguments 
            screen.blit(text_surface, (input_rect.x+10, input_rect.y+5))
            screen.blit(text_surface2, (input_rect2.x+10, input_rect2.y+5)) 
            screen.blit(text_surface3, (input_rect3.x+10, input_rect3.y+5))  
            
            # set width of textfield so that text cannot get 
            # outside of user's text input 
            '''input_rect.w = max(100, text_surface.get_width()+10) 

            input_rect2.w = max(100, text_surface2.get_width()+10)

            input_rect3.w = max(100, text_surface3.get_width()+10)'''
            
            # display.flip() will update only a portion of the 
            # screen to updated, not full area 
            pygame.display.flip() 
            
            # clock.tick(60) means that for every second at most 
            # 60 frames should be passed. 
            clock.tick(60)

    return nickname, ipAddress, port
