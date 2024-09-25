import React, { useState, useEffect } from 'react';
import { Helmet } from 'react-helmet';
import { useSelect } from 'downshift';
import { ChevronDownIcon } from '@heroicons/react/20/solid';
import './App.css';
import iGEMLogo from './assets/iGEM_logo.svg';
import { Popup } from 'reactjs-popup';

import Slider from '@mui/material/Slider';
import TextField from '@mui/material/TextField';
import Tabs from '@mui/material/Tabs';
import Tab from '@mui/material/Tab';

const App: React.FC = () => {
  const [selectedMode, setSelectedMode] = useState<string>('Off');
  const [selectedNode, setSelectedNode] = useState<number>(0);
  const {
    isOpen,
    getToggleButtonProps,
    getItemProps,
    getMenuProps,
    highlightedIndex,
    selectedItem,
  } = useSelect({
    items: ['Port 1', 'Port 2'],
    onSelectedItemChange: (changes) => console.log(changes.selectedItem),
  });
  const [selectedSensor, setSelectedSensor] = useState<string>('DHT11'); // Default sensor
  const {
    isOpen: sensorIsOpen,
    getToggleButtonProps: getSensorToggleButtonProps,
    getItemProps: getSensorItemProps,
    getMenuProps: getSensorMenuProps,
    highlightedIndex: sensorHighlightedIndex,
    selectedItem: sensorSelectedItem,
  } = useSelect({
    items: ['DHT11', 'OD600'],
    onSelectedItemChange: (changes) => {
      setSelectedSensor(changes.selectedItem);
      console.log("Selected Sensor:", changes.selectedItem);
    },
  });
  const [isPopupOpen, setIsPopupOpen] = useState(false);
  const [pumpSpeed, setPumpSpeed] = useState(50); // Default pump speed
  const [pumpDelay, setPumpDelay] = useState(2.5); // Default pump delay

  const handleAdvancedSettingsClick = () => {
    setIsPopupOpen(true);
  };

  const handleModeChange = (mode: string) => {
    setSelectedMode(mode);
  };

  const handleNodeClick = (index: number) => {
    setSelectedNode(index);
  };
  
  const handlePumpSpeedChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setPumpSpeed(parseFloat(event.target.value));
    setSliderValueLabelVisible(true); // Show the value label when dragging
  };

  const handlePumpDelayChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setPumpDelay(parseFloat(event.target.value));
  };
  const [selectedTab, setSelectedTab] = useState(0); // Initial selected tab
  const handleChange = (event: React.SyntheticEvent, newValue: number) => {
    setSelectedTab(newValue);
  };

  
  const nodeStyles = (index: number) => ({
    width: '20px',
    height:'20px',
    backgroundColor: selectedNode === index ? '#000' : '#fff',
    fontWeight: selectedNode === index ? 'bold' : 'normal',
    fontSize: '1.5rem',
    top: `${(index / 3 * 20) + 10}rem`,
  });

  return (
    <div className={`app ${isPopupOpen ? 'app-popup-open' : ''}`}>
      <header className="header">
	<img rel="icon" src={iGEMLogo} alt="UBC iGEM Logo" className="logo" />
	<div className="dropdown-container">
	  <button {...getToggleButtonProps()} className="dropdown-button">
	    {selectedItem || 'Select Port'}
	    <ChevronDownIcon className="dropdown-arrow" />
	  </button>
	  <ul
            {...getMenuProps()}
            className={'dropdown-menu ' + (isOpen ? 'open' : '')}
	  >
	    {isOpen &&
      ['Port 1', 'Port 2'].map((item, index) => (
            <li
              key={item}
              {...getItemProps({ item, index })}
              className={'dropdown-item ' + (highlightedIndex === index ? 'highlighted' : '')}
            >
              {item}
            </li>
	    ))}
	  </ul>
	</div>
      </header>

      <main className="main">
	<section className="controls">
	  <div className="vertical-line"></div> 
	  <div
	    className="node"
	    onClick={() => handleNodeClick(0)}
					      style={nodeStyles(0)}
	    >
	    <span>Off</span>
	  </div>
	  <div
            className="node"
            onClick={() => handleNodeClick(1)}
              style={nodeStyles(1)}
	    >
	    <span>Mixing mode</span>
	  </div>
	  <div
            className="node"
            onClick={() => handleNodeClick(2)}
              style={nodeStyles(2)}
	    >
	    <span>Bubbling mode</span>
	  </div>
	  <div
            className="node"
            onClick={() => handleNodeClick(3)}
              style={nodeStyles(3)}
	    >
	    <span>Fluid out</span>
	  </div>
	  <button className="advanced-settings-button" onClick={handleAdvancedSettingsClick}>
	    Advanced Settings
	  </button>
          <Popup open={isPopupOpen} onClose={() => setIsPopupOpen(false)}>
            <div className="popup-content">
              <div className="popup-element">
		<h3 className="popup-title">Pump Speed</h3>
		<p className="popup-info"> Affects all modes. Unit: %</p>
		<p className="popup-description">Controls the speed of the bioreactor pump.</p>
		<div className="popup-slider">
		  <Slider
		    value={pumpSpeed}
		    onChange={(event: Event, newValue: number | number[]) => {
					      if (typeof newValue === 'number') {
						setPumpSpeed(newValue);
					      }
					    }}
					    aria-labelledby="pump-speed-slider"
					    min={0}
					    max={100}
					    color="secondary"
            />
		    <TextField
                      type="number"
                      value={pumpSpeed}
                      onChange={handlePumpSpeedChange}
                      inputProps={{
                      min: 0,
                      max: 100,
                      style: { textAlign: 'left', width: '100px' } // Adjust width as needed
                }}
                sx={{ ml: '1rem', '& .MuiOutlinedInput-root': { '& fieldset': { border: 'none' } } }} // Remove border
		    />
		</div>
              </div>

              <div className="popup-element">
		<h3 className="popup-title">Pump Delay</h3>
		<p className="popup-info"> Affects mixing mode only. Unit: seconds</p>
		<p className="popup-description">Controls the delay between mixing and aeration.</p>
		<div className="popup-slider">
		  <Slider
		    value={pumpDelay}
		    onChange={(event: Event, newValue: number | number[]) => {
					      if (typeof newValue === 'number') {
						setPumpDelay(newValue);
					      }
					    }}
					    aria-labelledby="pump-delay-slider"
					    min={0.5}
					    max={20}
					    step={0.25}
					    color="secondary"
            />
		    <TextField
                      type="number"
                      value={pumpDelay}
                      onChange={handlePumpDelayChange}
                      inputProps={{
                      min: 0.5,
                      max: 20,
                      step: 0.25,
                      style: { textAlign: 'left', width: '100px' } // Adjust width as needed
                }}
                sx={{ ml: '1rem', '& .MuiOutlinedInput-root': { '& fieldset': { border: 'none' } } }} // Remove border
		    />
		</div>
              </div>

              <button onClick={() => setIsPopupOpen(false)}>Close</button>
            </div>
          </Popup>
	</section>

	<section className="display">
	  <div className="sensor-dropdown-container"> {/* Only for sensor dropdown */}
            <div {...getSensorToggleButtonProps()} className="sensor-title">
              <strong>{sensorSelectedItem || 'Sensor'}</strong>
              <ChevronDownIcon
		className="dropdown-arrow"
		style={{
		transform: sensorIsOpen ? 'rotate(180deg)' : 'rotate(0deg)',
								 transition: 'transform 0.2s ease', 
							       }}
              />
            </div>
            <ul 
	      {...getSensorMenuProps()}
	      className={'dropdown-menu ' + (sensorIsOpen ? 'open' : '')}
            >
              {sensorIsOpen &&
              ['DHT11', 'OD600'].map((item, index) => (
              <li
                key={item}
                {...getSensorItemProps({ item, index })}
                className={
                'dropdown-item ' +
                      (sensorHighlightedIndex === index ? 'highlighted' : '')
                  }
              >
                {item}
              </li>
              ))}
            </ul>
          </div> {/* Close sensor-dropdown-container */}

          <div className="sensor-tabs-container"> {/* Separate container for tabs */}
            <Tabs 
	      value={selectedTab} 
	      onChange={handleChange} 
	      textColor="secondary" 
	      indicatorColor="secondary"
            > 
              <Tab label="Tabulated Data" />
              <Tab label="Graph" />
              <Tab label="Raw CSV" />
              <Tab label="Downloads" />
            </Tabs>
          </div> {/* Close sensor-tabs-container */}
	</section>
      </main>
      <Helmet>
	<title>BioRX Control Panel | MK3</title>
	<link rel="icon" href={iGEMLogo}/>
      </Helmet>
    </div>
  );
};

export default App;
