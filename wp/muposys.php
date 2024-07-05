<?php

/*
Plugin Name: MUPOSYS
Plugin URI: https://github.com/azaeldevel/muposys/wp
Description: A implemetation of MUPOSYS over WordPress
Version: 0.1.0-alpha
Author: Your Name
Author URI: https://github.com/azaeldevel/muposys
*/

function wporg_options_page_html() 
{
	// check user capabilities
	if ( ! current_user_can( 'manage_options' ) ) {
		return;
	}
	?>
	<div class="wrap">
		<h1><?php echo esc_html( get_admin_page_title() ); ?></h1>
		<form action="options.php" method="post">
			<?php
			// output security fields for the registered setting "wporg_options"
			settings_fields( 'wporg_options' );
			// output setting sections and their fields
			// (sections are registered for "wporg", each field is registered to a specific section)
			do_settings_sections( 'wporg' );
			// output save settings button
			submit_button( __( 'Save Settings', 'textdomain' ) );
			?>
		</form>
	</div>
	<?php
}

function wporg_options_page()
{
	add_menu_page('Multi-Porpuse Software System', 'MUPOSYS', 'edit_posts', 'muposys', 'wporg_options_page_html', 'dashicons-admin-multisite', 4);
   add_submenu_page('muposys', __('Child Item'), __('Child Item'), 'edit_posts', 'Ventas', 'wporg_options_page_html');
}
add_action('admin_menu', 'wporg_options_page');

?>