/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * This code was an mConnectedThreadadaptation of BluetoothChat that came with Android SDK samples
 * This adaptation was made by Ricardo Lima Caratti, Ham radio, Callsign PU2CLR.
 * Brazil, 8/11/2012
 * 
 * 
 */

package br.eti.caratti.AntennaTuner;

// import com.example.android.BluetoothChat.R;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TabHost;
import android.widget.TextView;
import android.widget.Toast;

/**
 * This Activity presents the Antenna Tuner controls .
 */
@SuppressLint("NewApi")
public class BluetoothTuner extends Activity implements OnSeekBarChangeListener {

	// Remote Control servo limits
	
	
	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;

	// Key names received from the BluetoothChatService Handler
	public static final String DEVICE_NAME = "device_name";
	public static final String TOAST = "toast";

	// Intent request codes
	private static final int REQUEST_CONNECT_DEVICE = 1;
	private static final int REQUEST_ENABLE_BT = 2;

	// Layout Views
	private TextView titleApp;
	// Name of the connected device
	private String connectedDeviceName = null;
	
	private EditText feedBackPosition; 

	// Local Bluetooth adapter
	private BluetoothAdapter bluetoothAdapter = null;
	// Member object for the chat services
	private BluetoothService tunerService = null;

	TabHost tabHost;

	// ATU commands
	private SeekBar     seekbarTune;
	private SeekBar     seekbarMiddleTune; 	
	private SeekBar     seekbarFineTune; 
	private int         seekPos = 0;

	
	public static final int OFFSET = 800;   // 0 degree 
	public static final int MAXPOS = 1600;  // Max position 
	public static final int CENTER = 800;   // Center is CENTER + OFFSET
	
	public static final int MIDDLE_MAX_OFFSET = 120;
	public static final int MIDDLE_CENTER = 60;
	
	public static final int FINE_MAX_OFFSET = 20;
	public static final int FINE_CENTER = 10;
	
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Set up the window layout
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.main);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE,
				R.layout.custom_title);

		// Set up the custom title
		titleApp = (TextView) findViewById(R.id.title_left_text);
		titleApp.setText(R.string.app_name);
		titleApp = (TextView) findViewById(R.id.title_right_text);

		seekbarTune = (SeekBar) findViewById(R.id.seekBarTuner);
		seekbarTune.setMax(MAXPOS);
		seekbarTune.setProgress(CENTER);
		seekbarTune.setOnSeekBarChangeListener((OnSeekBarChangeListener) this);
		
		seekbarMiddleTune = (SeekBar) findViewById(R.id.SeekBarMiddleTuner);
		seekbarMiddleTune.setMax(MIDDLE_MAX_OFFSET);
		seekbarMiddleTune.setProgress(MIDDLE_CENTER);
		seekbarMiddleTune.setOnSeekBarChangeListener((OnSeekBarChangeListener) this);
		
		
		seekbarFineTune = (SeekBar) findViewById(R.id.SeekBarFineTuner);
		seekbarFineTune.setMax(FINE_MAX_OFFSET);
		seekbarFineTune.setProgress(FINE_CENTER);
		
		seekbarFineTune.setOnSeekBarChangeListener((OnSeekBarChangeListener) this);
		
 		
		// Get local Bluetooth adapter
		bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		
		feedBackPosition = (EditText) findViewById(R.id.editPosition) ;
		feedBackPosition.setEnabled(false);
		feedBackPosition.setFocusable(false);

		// If the adapter is null, then Bluetooth is not supported
		if (bluetoothAdapter == null) {
			Toast.makeText(this, "Bluetooth is not available",
					Toast.LENGTH_LONG).show();
			finish();
			return;
		}

	}

	@Override
	public void onStart() {
		super.onStart();

		if (!bluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
			// Otherwise, setup the chat session
		} else {
			if (tunerService == null)
				setupTuner();
		}
	}

	@Override
	public synchronized void onResume() {
		super.onResume();

		// Performing this check in onResume() covers the case in which BT was
		// not enabled during onStart(), so we were paused to enable it...
		// onResume() will be called when ACTION_REQUEST_ENABLE activity
		// returns.
		if (tunerService != null) {
			// Only if the state is STATE_NONE, do we know that we haven't
			// started already
			if (tunerService.getState() == BluetoothService.STATE_NONE) {
				// Start the Bluetooth services
				tunerService.start();
			}
		}
	}

	private void setupTuner() {
		tunerService = new BluetoothService(this, mHandler);

	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		// Stop the Bluetooth chat services
		if (tunerService != null)
			tunerService.stop();

	}

	private void ensureDiscoverable() {

		if (bluetoothAdapter.getScanMode() != BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE) {
			Intent discoverableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
			discoverableIntent.putExtra(
					BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
			startActivity(discoverableIntent);
		}
	}

	/**
	 * Sends a message.
	 * 
	 * @param message
	 *            A string of text to send.
	 */
	private void sendMessage(String message) {
		// Check that we're actually connected before trying anything
		if (tunerService.getState() != BluetoothService.STATE_CONNECTED) {
			Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT)
					.show();
			return;
		}

		// Check that there's actually something to send
		if (message.length() > 0) {
			// Get the message bytes and tell the BluetoothChatService to write
			byte[] send = message.getBytes();
			tunerService.write(send);

			// Reset out string buffer to zero and clear the edit text field
			// -- mOutStringBuffer.setLength(0);
			// -- mOutEditText.setText(mOutStringBuffer);
		}
	}
	


	// The Handler that gets information back from the BluetoothChatService
	private final Handler mHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case MESSAGE_STATE_CHANGE:
				switch (msg.arg1) {
				case BluetoothService.STATE_CONNECTED:
					titleApp.setText(R.string.title_connected_to);
					titleApp.append(connectedDeviceName);
					// -- mConversationArrayAdapter.clear();
					break;
				case BluetoothService.STATE_CONNECTING:
					titleApp.setText(R.string.title_connecting);
					break;
				case BluetoothService.STATE_LISTEN:
				case BluetoothService.STATE_NONE:
					titleApp.setText(R.string.title_not_connected);
					break;
				}
				break;
			case MESSAGE_DEVICE_NAME:
				// save the connected device's name
				connectedDeviceName = msg.getData().getString(DEVICE_NAME);
				Toast.makeText(getApplicationContext(),
						"Connected to " + connectedDeviceName,
						Toast.LENGTH_SHORT).show();
				break;
			case MESSAGE_TOAST:
				Toast.makeText(getApplicationContext(),
						msg.getData().getString(TOAST), Toast.LENGTH_SHORT)
						.show();
				break;
			}
		}
	};

	public void onActivityResult(int requestCode, int resultCode, Intent data) {

		switch (requestCode) {
		case REQUEST_CONNECT_DEVICE:
			// When DeviceListActivity returns with a device to connect
			if (resultCode == Activity.RESULT_OK) {
				// Get the device MAC address
				String address = data.getExtras().getString(
						DeviceListActivity.EXTRA_DEVICE_ADDRESS);
				// Get the BLuetoothDevice object
				BluetoothDevice device = bluetoothAdapter
						.getRemoteDevice(address);
				// Attempt to connect to the device
				tunerService.connect(device);
			}
			break;
		case REQUEST_ENABLE_BT:
			// When the request to enable Bluetooth returns
			if (resultCode == Activity.RESULT_OK) {
				// Bluetooth is now enabled, so set up a chat session
				setupTuner();
			} else {
				// User did not enable Bluetooth or an error occured
				Toast.makeText(this, R.string.bt_not_enabled_leaving,
						Toast.LENGTH_SHORT).show();
				finish();
			}
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.option_menu, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.scan:
			// Launch the DeviceListActivity to see devices and do scan
			Intent serverIntent = new Intent(this, DeviceListActivity.class);
			startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
			return true;
		case R.id.discoverable:
			// Ensure this device is discoverable by others
			ensureDiscoverable();
			return true;
		}
		return false;
	}
	
	
	public void handleLeftTuning(View v) {
		sendMessage("l");


	}

	public void handleRightTuning(View v) {
		sendMessage("r");

	}

	public void handlefastLeftTuning(View v) {
		sendMessage("L");
		
	}

	public void handlefastRightTuning(View v) {
		sendMessage("R");
	
	}

	public void handleMaxTuning(View v) {
		sendMessage("M");
		seekbarTune.setProgress(MAXPOS);
		seekbarMiddleTune.setProgress(MIDDLE_CENTER);
		seekbarFineTune.setProgress(FINE_CENTER);
		
	}

	public void handleMinTuning(View v) {
		sendMessage("m");
		seekbarTune.setProgress(0);
		seekbarMiddleTune.setProgress(MIDDLE_CENTER);
		seekbarFineTune.setProgress(FINE_CENTER);
	}

	public void handleCenterTuning(View v) {
		sendMessage("C");
		seekbarTune.setProgress(CENTER);
		seekbarMiddleTune.setProgress(MIDDLE_CENTER);
		seekbarFineTune.setProgress(FINE_CENTER);
	}

	public void handleBlueSetup(View v) {
		// Launch the DeviceListActivity to see devices and do scan
		Intent serverIntent = new Intent(this, DeviceListActivity.class);
		startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
	}


	public void handlePlusTuning(View v) {
		sendMessage("+");

	}

	public void handleMinusTuning(View v) {
		sendMessage("-");

	}

	public void handleScanTuning1(View v) {
		sendMessage("s");
	}

	public void handleScanTuning(View v) {
		sendMessage("S");
	}

	public void onProgressChanged(SeekBar seekBar, int progress,
			boolean fromUser) {
		// TODO Auto-generated method stub
		
		switch ( seekBar.getId() ) {
		case R.id.seekBarTuner:
			if ( Math.abs(seekPos - (progress + OFFSET) ) > 2 ) {
				seekPos = progress + OFFSET;
	 		    sendMessage("T"+seekPos+"#");
	 		    feedBackPosition.setText("Pos: "+ progress);
	 			seekbarFineTune.setProgress(FINE_CENTER);
			}			
			break;
		case R.id.SeekBarMiddleTuner: 
			sendMessage("F"+(seekPos + progress - MIDDLE_CENTER)+"#");
			break;
		case R.id.SeekBarFineTuner:
			sendMessage("F"+(seekPos + progress - FINE_CENTER)+"#");
			break;
		}

	}

	public void onStartTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
	}

	public void onStopTrackingTouch(SeekBar seekBar) {
		// TODO Auto-generated method stub
		// sendMessage("*"+seekPos+"#");
	}
	

}