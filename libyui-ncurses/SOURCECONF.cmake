SET( ${TARGETLIB}_SOURCES
  position.cc
  YNCursesUI.cc          
  NCtoY2Event.cc                  
  NCApplication.cc                
  NCWidgetFactory.cc              
  NCOptionalWidgetFactory.cc      

  NCPackageSelectorPluginStub.cc  

  NCtext.cc                       
  NCstring.cc                     
  stringutil.cc                   
  lang2encoding.cc      
  ncursesw.cc                     
  ncursesp.cc                     
  NCtypes.cc                      
  NCurses.cc                      
  NCstyle.cc                      
  NCStyleDef.cc                   
  NCTableItem.cc                  
  NCPad.cc                        
  NCButtonBox.cc                  
  NCTreePad.cc                    
  NCTablePad.cc                   
  NCTextPad.cc                    
  NCWidget.cc                     
  NCDialog.cc                     
  NCEmpty.cc                      
  NCSpacing.cc                    
  NCSquash.cc                     
  NCAlignment.cc                  
  NCFrame.cc                      
  NCCheckBoxFrame.cc              
  NCLayoutBox.cc                  
  NCReplacePoint.cc               
  NCRadioButtonGroup.cc           
  NCImage.cc                      
  NCCheckBox.cc                   
  NCLabel.cc                      
  NCProgressBar.cc                
  NCBusyIndicator.cc              
  NCMenuButton.cc                 
  NCPushButton.cc                 
  NCDumbTab.cc                    
  NCRadioButton.cc                
  NCInputField.cc                 
  NCIntField.cc                   
  NCComboBox.cc                   
  NCPadWidget.cc                  
  NCRichText.cc                   
  NCSelectionBox.cc               
  NCMultiSelectionBox.cc          
  NCTable.cc                      
  NCTree.cc                       
  NCLogView.cc                    
  NCMultiLineEdit.cc              
  NCFileSelection.cc              

  NCPopup.cc                      
  NCPopupTable.cc                 
  NCPopupList.cc                  
  NCPopupMenu.cc                  
  NCPopupTextEntry.cc             
  NCPopupInfo.cc                  
  NCAskForDirectory.cc            
  NCAskForFile.cc
)

SET( ${TARGETLIB}_HEADERS
  stdutil.h               
  NCi18n.h                
  tnode.h                 
  position.h              
  YNCursesUI.h            
  NCtoY2Event.h           
  NCApplication.h         
  NCWidgetFactory.h       
  NCOptionalWidgetFactory.h       

  NCPackageSelectorPluginStub.h   
  NCPackageSelectorPluginIf.h     
  NCtext.h                
  NCstring.h              
  stringutil.h            
  ncursesw.h              
  ncursesp.h              
  NCtypes.h               
  NCurses.h               
  NCstyle.h               
  NCStyleDef.h            
  NCTableItem.h           
  NCPad.h                 
  NCButtonBox.h           
  NCTreePad.h             
  NCTablePad.h            
  NCTextPad.h             
  NCWidget.h              
  NCDialog.h              
  NCEmpty.h               
  NCSpacing.h             
  NCSquash.h              
  NCAlignment.h           
  NCFrame.h               
  NCCheckBoxFrame.h       
  NCLayoutBox.h           
  NCReplacePoint.h        
  NCRadioButtonGroup.h    
  NCImage.h               
  NCCheckBox.h            
  NCLabel.h               
  NCProgressBar.h         
  NCBusyIndicator.h       
  NCMenuButton.h          
  NCPushButton.h          
  NCDumbTab.h             
  NCRadioButton.h         
  NCInputField.h          
  NCIntField.h            
  NCComboBox.h            
  NCPadWidget.h           
  NCRichText.h            
  NCSelectionBox.h        
  NCMultiSelectionBox.h   
  NCTable.h               
  NCTree.h                
  NCLogView.h             
  NCMultiLineEdit.h       
  NCFileSelection.h       
  NCPopup.h               
  NCPopupTable.h          
  NCPopupList.h           
  NCPopupMenu.h           
  NCPopupTextEntry.h      
  NCPopupInfo.h           
  NCAskForDirectory.h     
  NCAskForFile.h          
  NCstyle.braille.h NCstyle.mono.h        
  NCstyle.linux.h NCstyle.xterm.h         
  NCstyle.rxvt.h
)