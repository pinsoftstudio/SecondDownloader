   M S B A M L   `   `   `  ����@  <setup, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:setupsetup  5          setup.finish   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      %localclr-namespace:setup     5        N� Title$  finish��5	       � 	Resources 5   
    �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers :� RoutedEvent	 �� TargetProperty	
 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse��%/  &	        �� 5      " ��6   .�5      ��  � ��
 �����6/   �� 5       � �� �#2983cc6/   �� 5       �@�Cursor$
 Hand��6+   �� 5       � �� 5      �� 5      " ��6*   .R�5      �� #��z��6%   $ 6��6O   ._�5   "   �� $��Center=�63   $��Center=�6P   5      5      5       5      :� 5      $ Button.MouseEnter��6#   [�5      �� 5      .��5   "   �� .��5   &   �� $1	 +(Button.Background).(SolidColorBrush.Color)�65   $
 #4f9dddX�5   %   $ 0:0:0.1D�62   $ HoldEnd=�6E   6^   5$   #   5%      5'      :� 5(      $ Button.MouseLeave��6#   [�5)      �� 5*      .��5+   "   �� .��5,   &   �� $1	 +(Button.Background).(SolidColorBrush.Color)�65   $
 #2983ccX�5-   %   $ 0:0:0.1D�62   6G   5/   #   50      52      :� 53      $ Button.Click��6#   [�54      �� 55      .��56   "   �� .��57   &   W� $	 (Button.Opacity)�58      $ 1X�59      $	 0.8X�6   $ 0:0:0.2D�6    . 6,   5:   #   5;      5=      5?      5A      .��5B   
   � 
�������.+�5C      �� $
��Left=�6   $	��111��6/   $��Center=�6<   $	��115��6W   $��	/logo.png��6c   $��	55,0,0,40q�6v    J� OpacityMask 5D      �� 5E       �� ImageSource$ 	/logo.png��6!    j� TileMode$
 None=�69    j� Stretch$ Uniform=�6I   5G      �� 5H      $��SecondDownloader��6   $
��Left=�6/   $��
186,0,0,80q�6J   $��Center=�6^   $��Microsoft YaHei UI)�6y   $��25(�6�   �� 5I      $$��卸载完成，后会有期！��6   $
��Left=�6)   $��188,34,0,10q�6D   $��Center=�6Y   $��Microsoft YaHei UI)�6t   $��15(�6�   �� 5J      $ ��Developed by PinsoftStudio��6   $
��Left=�69   $��
188,0,0,24q�6T   $��Center=�6h   $��Cascadia Code)�6�   �� 5L   
   -   5        $��关闭��5L      #��[  6   $��Microsoft YaHei UI)�6A   $��15(�6a   $��	0,0,10,10q�6o   $��60��6�   $��35��6�   $��Right=�6�   $��Bottom=�6�    �� 	ClickMode$ Press=�6�   6�   5M      5O      